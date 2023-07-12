Description of Files/Programs in Repository:

encode.c: This C file contains the main() function for the encode program.

decode.c: This C file contains the main() function for the decode program.

trie.c: This C file is the source file for the Trie ADT.

trie.h: This header file specifies the interface for the Trie ADT.

word.c: This C file is the source file for the Word ADT.

word.h: This header file specifies the interface for the Word ADT.

io.c: This C file is the source file for the I/O module.

io.h: This header file specifies the interface for the I/O module.

endian.h: This header file specifies the interface for the endianness module.

code.h: This header file contains macros for reserved codes.

Makefile: This file directs the compilation process of encode.c and decode.c.

README.md: This file, which is Markdown format, is the current file you are reading and describes how to use my program and Makefile. It also lists and explains the different command-line options that my program accepts.

DESIGN.pdf: This file is a PDF version of my design document for assignment 6. It describes my design and design process for my program with pseudocode and images.

WRITEUP.pdf: This file is a PDF version of my writeup for assignment 6. It includes everything I learned from this assignment.

How to Build the Programs:

To compile encode.c, a user can use the Makefile to do so. With the Makefile, a user can type in terminal, as long as they're in the same directory as all the files, "make", "make all" or "make encode" to compile the C program.

To compile decode.c, a user can use the Makefile to do so. With the Makefile, a user can type in terminal, as long as they're in the same directory as all the files, "make", "make all" or "make decode" to compile the C program.

How to Run the Program:

After compiling encode.c and/or decode.c, a user can type in the terminal "./encode" and/or "./decode" with or without command-line arguments following it.

encode.c accepts four command-line options: -v, -i, -o, and -h.

-v: This command-line option displays compression statistics. To run this command-line option in terminal using encode.c, we would first compile encode.c and run the command: "./encode -v".

-i input: This command-line option specifies the input to compress. The default input is stdin. To run this command-line option in terminal using encode.c, we would first compile encode.c and run the command: "./encode -i input" where input is a file. If this command-line option is enabled without a file following -i, my program will output an error message and display the program usage.

-o output: This command-line option specifies the output of compressed input. The default input is stdout. To run this command-line option in terminal using encode.c, we would first compile encode.c and run the command: "./encode -o output" where output is a file. If this command-line option is enabled without a file following -o, my program will output an error message and display the program usage. If the user specifies a file that does not exist in a directory you can access, the program will create that output file. If the user is in a directory that you can't access and specifies a file that does not exist, the program will output an erorr message.

-h: This command-line option displays program synopsis and usage. To run this command-line option in terminal using encode.c, we would first compile encode.c and run the command: "./encode -h ".

decode.c accepts four command-line options: -v, -i, -o, and -h.

-v: This command-line option displays compression statistics. To run this command-line option in terminal using decode.c, we would first compile decode.c and run the command: "./decode -v".

-i input: This command-line option specifies the input to decompress. The default input is stdin. To run this command-line option in terminal using decode.c, we would first compile decode.c and run the command: "./decode -i input" where input is a file. If this command-line option is enabled without a file following -i, my program will output an error message and display the program usage.

-o output: This command-line option specifies the output of decompressed input. The default input is stdout. To run this command-line option in terminal using decode.c, we would first compile decode.c and run the command: "./decode -o output" where output is a file. If this command-line option is enabled without a file following -o, my program will output an error message and display the program usage. If the user specifies a file that does not exist in a directory you can access, the program will create that output file. If the user is in a directory that you can't access and specifies a file that does not exist, the program will output an erorr message.

-h: This command-line option displays program synopsis and usage. To run this command-line option in terminal using decode.c, we would first compile decode.c and run the command: "./decode -h ".

Example of how to use my program:

To compress/encode a file and outputting the result into another file, a user would run the following command after compilation in the terminal: "./encode -i alex.txt -o middle.txt". This command would encode alex.txt and store the compression in middle.txt. To decompress/decode the encoded file, a user would run the following command after compilation in the terminal: ./decode -i middle.txt -o output.txt". This command would decode middle.txt and store the decompression in output.txt, which should be the same as alex.txt if encoded/decoded properly.

How to Clean Assignment Directory:

In the assignment directory, a user can type in terminal "make clean" and this command will remove all object and executable files from the directory.

How to Format Files in Directory:

In the assignment directory, a user can type in terminal "make format" and all of the code will be formatted.

Citations:

Lev(tutor) helped me with the following functions in io.c: read_sym, write_bit, write_pair, read_bit, read_pair, 

Miles(tutor) helped me with the function "write_word" in io.c.

Dev(TA) helped me with the function "flush_pairs" in io.c.