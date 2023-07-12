Description of Files/Programs in Repository:

universe.c: This C file implements the Universe ADT.

universe.h: This header file specifies the interface to the Universe ADT.

life.c: This C file contains the main function and other functions necessary to complete my implementation of the Game of Life.

Makefile: This file directs the compilation process of life.c.

README.md: This file, which is Markdown format, is the current file you are reading and describes how to use my program and Makefile. It also lists and explains the different command-line options that my program accepts.

DESIGN.pdf: This file is a PDF version of my design document for assignment 4. It describes my design and design process for my program with pseudocode and images.

WRITEUP.pdf: This file is a PDF version of my writeup for assignment 4. It includes everything that I learned from the assignment, how I made use of the ncurses library, the insights I obtained about the process of compiling/linking from this assignment, and my understading of Conway's game of life.

How to Build the Program:

To compile life.c, a user can use the Makefile to do so. With the Makefile, a user can type in terminal, as long as they're in the same directory as all the files, "make", "make all" or "make life" to compile the C program.

How to Run the Program:

After compiling sorting.c, a user can type "./life" with or without command-line arguments following it.

life.c accepts six command-line options: -t, -s, -n, -i, -o, and -h.

-t: This command-line option specifies that the Game of Life is to be played in a toroidal universe. To run this command-line option in terminal using life.c, we would first compile life.c and run the command: "./life -t".

-s: This command-line option silences ncurses. Enabling this option means that nothing should be displayed by ncurses. To run this command-line option in terminal using life.c, we would first compile life.c and run the command: "./life -s".

-n generations: This command-line option specifies the number of generations that the universe goes through. The default number of generations if this command-line option is not specified is 100. To run this command-line option in terminal using life.c, we would first compile life.c and run the command: "./life -t generations" where generations is a number such as 50.

-i input: This command-line option specifies the input file to read in order to populate the universe. The default input if this command-line option is not specified is stdin. To run this command-line option in terminal using life.c, we would first compile life.c and run the command: "./life -i input" where input is an input file such as 101.txt. If the user provides an input file that does not exist, such as nothing.txt, terminal will print "Error opening nothing.txt".

-o output: This command-line option specifies the output file to print the final state of the universe. The default output if this command-line option is not specified is stdout. To run this command-line option in terminal using life.c, we would first compile life.c and run the command: "./life -o output" where output is an output file such as output.txt. If the user provides an output file that does not exist, such as nothing.txt, terminal will print the final state of the universe in a newly created file "nothing.txt".

-h: This command-line option displays a help message detailing program usage. To run this command-line option in terminal using life.c, we would first compile life.c and run the command: "./life -h". If a user uses the "-h" command line option, the program will ignore any other command-line options specified. For example, running the command "./life -h -s -i ./lists/101.txt" will display the help message and not output anything else.

How to Clean Assignment Directory:

In the assignment directory, a user can type in terminal "make clean" and this command will remove all object and executable files from the directory.

How to Format Files in Directory:

In the assignment directory, a user can type in terminal "make format" and all of the code will be formatted.

Citations:

Lev(tutor) helped me write the uv_populate and uv_census functions in universe.c
