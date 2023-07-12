#!/bin/bash
make clean && make monte_carlo

# 3nd column is x coordinate
# 4th column is y coordinate
# 5th column is 1 if point is in circle, 0 if not

# if fifth column = 1 print the points inside the circle
./monte_carlo -n 1000 | awk '{if($5 == 1) print $3, $4}' > in_circle.dat
# if fifth column = 0 print the points outside the circle
./monte_carlo -n 1000 | awk '{if($5 == 0) print $3, $4}' > out_circle.dat

# plot figure 2

gnuplot << END
    set terminal pdf
    set output "figure_2.pdf"
    set size square
    set xrange [0:1]
    set yrange [0:1]
    set xtics 0.2
    set ytics 0.2
    f(x) = (1 - x**2)**0.5
    plot f(x) notitle with lines lw 0.5 lt rgb "black", "in_circle.dat" notitle with points pt 7 ps 0.25 lc rgb "blue", "out_circle.dat" notitle with points pt 7 ps 0.25 lc rgb "red"
END

# empty data files
> in_circle.dat
> out_circle.dat

PI=3.1415926535

for i in {1..5} 
do
./monte_carlo -n 32000 -r $i | tail -n 32000 | awk '{print $1, $2 - '$PI'}' > "error_estimation_$i".dat
done
# 3.14 - estimate

# plot figure 3
gnuplot << END
    set terminal pdf
    set output "figure_3.pdf"
    set title "Monte Carlo Error Estimation"
    set ylabel "Error"
    set xrange [1:25000]
    set yrange [-1:1]
    set for [i=0:7] xtics (0,4**i)
    set logscale x 4
    set ytics 0.5
    plot "error_estimation_1.dat" notitle with lines, "error_estimation_2.dat" notitle with lines, "error_estimation_3.dat" notitle with lines, "error_estimation_4.dat" notitle with lines, "error_estimation_5.dat" notitle with lines
END

# empty data files
> error_estimation_1.dat
> error_estimation_2.dat
> error_estimation_3.dat
> error_estimation_4.dat
> error_estimation_5.dat

# first extra plot

for i in {1..5} 
do
./monte_carlo -n 32000 -r $i | tail -n 32000 | awk '{print $1, $2 - '$PI'}' > "low_iterations_$i".dat
done
# 3.14 - estimate

# plot extra plot of low iterations
gnuplot << END
    set terminal pdf
    set output "low_iterations.pdf"
    set title "Monte Carlo Error Estimation of Low Iterations"
    set xlabel "Iterations"
    set ylabel "Error"
    set xrange [1:64]
    set yrange [-1:1]
    set xtics 8
    set ytics 0.5
    plot "low_iterations_1.dat" notitle with lines, "low_iterations_2.dat" notitle with lines, "low_iterations_3.dat" notitle with lines, "low_iterations_4.dat" notitle with lines, "low_iterations_5.dat" notitle with lines
END

# empty data files
> low_iterations_1.dat
> low_iterations_2.dat
> low_iterations_3.dat
> low_iterations_4.dat
> low_iterations_5.dat


# second extra plot

for i in {1..5} 
do
./monte_carlo -n 32000 -r $i | tail -n 32000 | awk '{print $1, $2 - '$PI'}' > "high_iterations_$i".dat
done
# 3.14 - estimate

# plot extra plot of high iterations
gnuplot << END
    set terminal pdf
    set output "high_iterations.pdf"
    set title "Monte Carlo Error Estimation of High Iterations"
    set xlabel "Iterations"
    set ylabel "Error"
    set xrange [1024:25000]
    set yrange [-0.5:0.5]
    set logscale x 4
    set ytics 0.25
    plot "high_iterations_1.dat" notitle with lines, "high_iterations_2.dat" notitle with lines, "high_iterations_3.dat" notitle with lines, "high_iterations_4.dat" notitle with lines, "high_iterations_5.dat" notitle with lines
END

# empty data files
> high_iterations_1.dat
> high_iterations_2.dat
> high_iterations_3.dat
> high_iterations_4.dat
> high_iterations_5.dat
