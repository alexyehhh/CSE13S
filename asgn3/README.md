Description of Files/Programs in Repository:

batcher.c: This C file implements Batcher sort.

batcher.h: This header file specifies the interface to batcher.c.

shell.c: This C file implements Shell sort.

shell.h: This header file specifies the iterface to shell.c.

heap.c: This C file implements Heap sort.

heap.h: This header file specifies the interface to heap.c.

quick.c: This C file implements recursive Quicksort.

quick.h: This header file specifies the interface to quick.c.

set.c: This C file implements bit-wise Set operations.

set.h: This header file implements and specifies the interface for the set ADT.

stats.c: This C file implements the statistics module.

stats.h: This header file specifies the interface to the statistics module.

sorting.c: This C file contains main() and contains other functions necessary to complete the assignment.

Makefile: This file directs the compilation process of sorting.c.

README.md: This file, which is Markdown format, is the current file you are reading and describes how to use my program and Makefile. It also lists and explains the different command-line options that my program accepts.

DESIGN.pdf: This file is a PDF version of my design document for assignment 3. It describes my design and design process for my program with pseudocode and images.

WRITEUP.pdf: This file is a PDF version of my writeup for assignment 3. I wrote about what I learned from the different sorting algorithms. I also included graphs explaining the performance of the sorts on a variety of inputs and an analysis of the graphs I produced.

How to Build the Program:

To compile sorting.c, a user can use the Makefile to do so. With the Makefile, a user can type in terminal, as long as they're in the same directory as all the files, "make", "make all" or "make sorting" to compile the C program.

How to Run the Program:

After compiling sorting.c, a user can type "./sorting" with command line arguments following it.

Command-line Options that sorting.c Accepts:

sorting.c accepts nine command line options: -a, -h, -b, -s, -q, -r, -n, -p, and -H.

-a: This command-line option employs all sorting algorithms. To run this command-line option in terminal using sorting.c, we would first compile mathlib-test.c and run the command: "./sorting -a".

-h: This command-line option enables heap sort. To run this command-line option in terminal using sorting.c, we would first compile sorting.c and run the command: "./sorting -h".

-b: This command-line option enables batcher sort. To run this command-line option in terminal using sorting.c, we would first compile sorting.c and run the command: "./sorting -b".

-s: This command-line option enables shell sort. To run this command-line option in terminal using sorting.c, we would first compile sorting.c and run the command: "./sorting -s".

-q: This command-line option enables quick sort. To run this command-line option in terminal using sorting.c, we would first compile sorting.c and run the command: "./sorting -q".

-r seed: This command-line option sets the random seed to seed. The default seed is 13371453 if this command-line option is not specified. To run this command-line option in terminal using sorting.c, we would first compile sorting.c and run the command "./sorting -r seed" with "seed" being a number. If no seed is specified (./sorting -r), terminal will say "./sorting: option requires an argument -- 'r'" and will print the help message.

-n size: This command-line option sets the array size to size. The default size is 100 if this command-line option is not specified. To run this command-line option in terminal using sorting.c, we would first compile sorting.c and run the command: "./sorting -n size" with "size" being a number. If no size is specified (./sorting -n), terminal will say "./sorting: option requires an argument -- 'n'" and will print the help message.

-p elements: This command-line option prints out "elements" number of elements from the array. The default number of elements to print out is 100 if this command-line option is not specified. If the size of the array is less than the specified number of elements to print, the entire array is printed. To run this command-line option in terminal using sorting.c, we would first compile sorting.c and run the command "./sorting -p elements" with "elements" being a number. If no seed is specified (./sorting -p), terminal will say "./sorting: option requires an argument -- 'p'" and will print the help message.

-H: This command-line option displays a help message detailing program usage. To run this command-line option in terminal using sorting.c, we would first compile sorting.c and run the command: "./sorting -H". If a user uses the "-H" command line option, the program will not enable any sorts. For example, running the command "./sorting -b -s -H" will display the help message and not enable the batcher sort or shell sort.

How to Clean Assignment Directory:

In the assignment directory, a user can type in terminal "make clean" and this command will remove all object and executable files from the directory.

How to Format Files in Directory:

In the assignment directory, a user can type in terminal "make format" and all of the code will be formatted.

Citations:

Miles(tutor) helped me write a function to calculate the bit length of an input in batcher.c.