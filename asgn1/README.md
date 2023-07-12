Description of Files/Programs in Repository:

plot.sh: This file is a bash script that produces plots of the C program "monte_carlo.c". 

monte_carlo.c: This file prints the Monte Carlo estimation for pi after each random point it tests.

Makefile: This file directs the compilation process of the Monte Carlo program.

README.md: This file, which is Markdown format, is the current file you are reading and describes how to use my script and Makefile. It also lists and explains the different command-line options that my program accepts.

DESIGN.pdf: This file is a PDF of my design document for assignment 1. It describes my design and design process for my program with pseudocode and images.

WRITEUP.pdf: This file is a PDF of my writeup for assignment 1. It includes the plots that I produced using my bash script, as well as discussion on which UNIX commands I used to produce each plot and why I chose to use them.

How to Build the Program:

./plot.sh will compile monte_carlo.c. To compile monte_carlo.c separately, a user can use the Makefile to do so. With the Makefile, a user can type in terminal, as long as they're in the same directory as all the files, "make all" or "make monte_carlo.c" to compile the C program. 

How to Run the Program:

After compiling monte_carlo.c, a user can type "./plot.sh" in terminal and the outputted pdfs of the plots will appear in the same directory as all the files.

How to Clean Assignment Directory:

In the assignment directory, a user can type in terminal "make clean" and this command will remove all object and executable files from the directory.

How to Format Files in Directory:

In the assignment directory, a user can type in terminal "make format" and all of the code will be formatted.

Command-line Options that monte_carlo.c Accepts:

monte_carlo.c accepts two command line options: -n and -r. 

-n points specifies the number of points for each Monte Carlo estimation of pi. For example, if we wanted to test 20 points, we would use the command-line option "-n 10". To run this command-line option in terminal using monte_carlo.c, we would first compile monte_carlo.c and run the command: "./monte_carlo -n 10".

-r seed specifies the deterministic random starting point. For example, if we wanted to run monte_carlo.c with the default number of points (20) with a random seed of 20, we would use the command-line option "-r 20". To run this command-line option in terminal using monte_carlo.c, we would first compile monte_carlo.c and run the command: "./monte_carlo -n 10".

monte_carlo.c can accept both command-line options at the same time as well. For example, running the command "./monte_carlo -n 20 -r 20" would run the Monte Carlo estimations using 20 points and a seed of 20.
