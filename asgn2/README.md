Description of Files/Programs in Repository:

bbp.c: This C file contains the implementation of the Bailey-Borwein-Plouffe formula to approximate pi and the function to return the number of computed terms. 

e.c: This C file contains the implementation of the Taylor series to approximate Euler's number e and the function to return the number of computed terms.

euler.c: This C file contains the implementation of Euler's solution to approximate pi and the function to return the number of computed terms.

madhava.c: This C file contains the implementation of the Madhava series to approximate pi and the function to return the number of computed terms.

mathlib-test.c: This C file contain the main function which tests each of my math library functions.

mathlib.h: This header file contains the interface for my math library.

newton.c: This C file contains the implementation of the square root approximation using Newton's method and the function to return the number of computed iterations.

viete.c: This C file contains the implementation of Viete's formula to approximate pi and the function to return the number of computed factors.

Makefile: This file directs the compilation process of mathlib-test.c

README.md: This file, which is Markdown format, is the current file you are reading and describes how to use my script and Makefile. It also lists and explains the different command-line options that my program accepts.

DESIGN.pdf: DESIGN.pdf: This file is a PDF of my design document for assignment 2. It describes my design and design process for my program with pseudocode and images.

WRITEUP.pdf: WRITEUP.pdf: This file is a PDF version of my writeup for assignment 2. It contains graphs displaying the difference between the values reported by my implemented functions and that of the math library. It also contains analysis and explanations for any discrepancies and findings that I gleaned from my testing.

How to Build the Program:

To compile mathlib-test.c, a user can use the Makefile to do so. With the Makefile, a user can type in terminal, as long as they're in the same directory as all the files, "make all" or "make mathlib-test.c" to compile the C program.

How to Run the Program:

After compiling mathlib-test.c, a user can type "./mathlib-test" with command line arguments following it.

Command-line Options that mathlib-test.c Accepts:

mathlib-test.c accepts nine command line options: -a, -e, -b, -m, -r, -v, -n, -s, and -h.

-a: This option runs all tests for all functions in the math library. To run this command-line option in terminal using mathlib-test.c, we would first compile mathlib-test.c and run the command: "./mathlib-test -a".

-e: This option runs the e approximation test. To run this command-line option in terminal using mathlib-test.c, we would first compile mathlib-test.c and run the command: "./mathlib-test -e".

-b: This option runs the Bailey-Borwein-Plouffe (bbp) pi approximation test. To run this command-line option in terminal using mathlib-test.c, we would first compile mathlib-test.c and run the command: "./mathlib-test -b".

-m: This option runs the Madhava pi approximation test. To run this command-line option in terminal using mathlib-test.c, we would first compile mathlib-test.c and run the command: "./mathlib-test -m".

-r: This option runs the Euler sequence pi approximation test. To run this command-line option in terminal using mathlib-test.c, we would first compile mathlib-test.c and run the command: "./mathlib-test -r".

-v: This option runs the Viete pi approximation test. To run this command-line option in terminal using mathlib-test.c, we would first compile mathlib-test.c and run the command: "./mathlib-test -v".

-n: This option runs the Newton-Raphson square root approximation test. To run this command-line option in terminal using mathlib-test.c, we would first compile mathlib-test.c and run the command: "./mathlib-test -n".

-s: This option enables the printing of statistics to see the computed terms and factors for each tested function. To run this command-line option in terminal using mathlib-test.c, we would first compile mathlib-test.c and run the command line option "-s" after another command line argument besides "-h". For example, to see the statistics of running the e approximation test, a user would type in terminal: "./mathlib-test -e -s Running "./mathlib-test -s" will display the help message because the "-s" command line option must be used with another command line option.

-h: This option displays a help message detailing program ussage. To run this command-line option in terminal using mathlib-test.c, we would first compile mathlib-test.c and run the command: "./mathlib-test -h". If a user uses the "-h" command line option, the program will not run any tests. For example, running the command "./mathlib-test -e -s -h" will display the help message and not run the e approximation test with statistics.

How to Clean Assignment Directory:

In the assignment directory, a user can type in terminal "make clean" and this command will remove all object and executable files from the directory.

How to Format Files in Directory:

In the assignment directory, a user can type in terminal "make format" and all of the code will be formatted.

Citations:

Lev(tutor) helped me with the function double pi_viete(void)
