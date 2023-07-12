Description of Files/Programs in Repository:

decrypt.c: This C file contains the implementation and main() function for the decrypt program.

encrypt.c: This C file contains the implementation and main() function for the encrypt program.

keygen.c: This C file contains the implementation and main() function for the keygen program.

numtheory.c: This C file contains the implementations of the number theory functions.

numtheory.h: This header file specifies the interface for the number theory functions.

randstate.c: This C file contains the implementation of the random state interface for the SS library and number theory functions.

randstate.h: This header file specifies the interface for initializing and clearing the random state.

ss.c: This C file contains the implementation of the SS library.

ss.h: This header file specifies the interface for the SS library.

Makefile: This file directs the compilation process of keygen.c, encrypt.c, and decrypt.c.

README.md: This file, which is Markdown format, is the current file you are reading and describes how to use my program and Makefile. It also lists and explains the different command-line options that my program accepts.

DESIGN.pdf: This file is a PDF version of my design document for assignment 5. It describes my design and design process for my program with pseudocode and images.

WRITEUP.pdf: This file is a PDF version of my writeup for assignment 5. It includes everything that I learned in this assignment. It also includes the applications of of public-private cryptography, how it influences the world today, and one way that I personally take advantage of public-private cryptography on a day-to-day basis.

How to Build the Programs:

To compile keygen.c, a user can use the Makefile to do so. With the Makefile, a user can type in terminal, as long as they're in the same directory as all the files, "make", "make all" or "make keygen" to compile the C program.

To compile encrypt.c, a user can also use the Makefile to do so. With the Makefile, a user can type in terminal, as long as they're in the same directory as all the files, "make", "make all" or "make encrypt" to compile the C program.

To compile decrypt.c, a user can also use the Makefile to do so. With the Makefile, a user can type in terminal, as long as they're in the same directory as all the files, "make", "make all" or "make decrypt" to compile the C program.

How to Run the Program:

After compiling keygen.c, encrypt.c, and/or decrypt.c, a user can type in the terminal "./keygen", "./encrypt", and/or "./decrypt" with or without command-line arguments following it.

keygen.c accepts seven command-line options: -b, -i, -n, -d, -s, -v, and -h.

-b bits: This command-line option specifies the minimum bits needed for the public modulus n. The default number of bits is 256. To run this command-line option in terminal using keygen.c, we would first compile keygen.c and run the command: "./keygen -b bits" where bits is a number. If this command-line option is enabled without a number of bits following -b, my program will output an error message and display the program usage.

-i iterations: This command-line option specifies the number of Miller-Rabin iterations for testing primes. The default number of iterations is 50. To run this command-line option in terminal using keygen.c, we would first compile keygen.c and run the command: "./keygen -i iterations" where iterations is a number. If this command-line option is enabled without a number of iterations following -i, my program will output an error message and display the program usage.

-n pbfile: This command-line option specifies the public key file. The default public key file is ss.pub. To run this command-line option in terminal using keygen.c, we would first compile keygen.c and run the command: "./keygen -n pbfile" where pbfile is a file. If the pbfile doesn't exist, my program will output an error message.

-d pvfile: This command-line option specifies the private key file. The default private key file is ss.priv. To run this command-line option in terminal using keygen.c, we would first compile keygen.c and run the command: "./keygen -d pvfile" where pvfile is a file. If the pvfile doesn't exist, my program will output an error message.

-s seed: This command-line option specifies the random seed for the random state initialization. The default seed is the seconds since the UNIX epoch, given by time(NULL). To run this command-line option in terminal using keygen.c, we would first compile keygen.c and run the command: "./keygen -s seed" where seed is a number. If this command-line option is enabled without a seed following -s, my program will output an error message and display the program usage.

-v: This command-line option enables verbose output. To run this command-line option in terminal using keygen.c, we would first compile keygen.c and run the command: "./keygen -v".

-h: This command-line option displays program synopsis and usage. To run this command-line option in terminal using keygen.c, we would first compile keygen.c and run the command: "./keygen -h ".

encrypt.c accepts five command-line options: -i, -o, -n, -v, and -h.

-i infile: This command-line option specifies the input file to encrypt. The default input file is stdin. To run this command-line option in terminal using keygen.c, we would first compile keygen.c and run the command: "./encrypt -i infile" where infile is a file. If the infile doesn't exist, my program will output an error message.

-o outfile: This command-line option specifies the output file to encrypt. The default output file is stdout. To run this command-line option in terminal using keygen.c, we would first compile keygen.c and run the command: "./encrypt -o outfile" where outfile is a file. If the outfile doesn't exist, my program will create that new file in the directory.

-n pbfile: This command-line option specifies the file containing the public key. The default file is ss.pub. To run this command-line option in terminal using keygen.c, we would first compile keygen.c and run the command: "./encrypt -n pbfile" where pbfile is a file. If the pbfile doesn't exist, my program will output an error message.

-v: This command-line option enables verbose output.

-h: This command-line option displays program synopsis and usage.

decrypt.c accepts five command-line options: -i, -o, -n, -v, and -h.

-i infile: This command-line option specifies the input file to decrypt. The default input file is stdin. To run this command-line option in terminal using keygen.c, we would first compile keygen.c and run the command: "./encrypt -i infile" where infile is a file. If the infile doesn't exist, my program will output an error message.

-o: This command-line option specifies the output file to decrypt. The default output file is stdout. To run this command-line option in terminal using keygen.c, we would first compile keygen.c and run the command: "./encrypt -o outfile" where outfile is a file. If the outfile doesn't exist, my program will create that new file in the directory.

-n pvfile: This command-line option specifies the file containing the private key. The default file is ss.priv. To run this command-line option in terminal using keygen.c, we would first compile keygen.c and run the command: "./encrypt -n pvfile" where pvfile is a file. If the pvfile doesn't exist, my program will output an error message.

-v: This command-line option enables verbose output.

-h: This command-line option displays program synopsis and usage. 

Example of how to use my program:

To generate a public and private key, a user would run the following command after compilation in the terminal: "./keygen". To encrypt a file using these keys and output the encrypted message, a user would run the following command after compilation in the terminal: "./encrypt -i input.txt -o encryption.txt". This would encrypt the file input.txt and output the encrypted message in encryption.txt. To decrypt a file and decrypt the encrypted message, a user would run the following command after compilation in the terminal: "./decrypt -i encryption.txt -o output.txt". This would decrypt the file encryption.txt and output the decrypted message in output.txt.

How to Clean Assignment Directory:

In the assignment directory, a user can type in terminal "make clean" and this command will remove all object and executable files from the directory.

How to Format Files in Directory:

In the assignment directory, a user can type in terminal "make format" and all of the code will be formatted.

Citations:

Lev(tutor) helped me write a helper function called find_s_and_r used in my is_prime function in numtheory.c.