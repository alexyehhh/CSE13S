EXECBIN = mathlib-test
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

# All available .c files are included as SOURCES
SOURCES = $(wildcard *.c)

# Each .c file has a corresponding .o file
OBJECTS = $(SOURCES:%.c=%.o)

# These are "phony" targets: they're not real files
.PHONY: all clean spotless format

all: $(EXECBIN)

mathlib-test: mathlib-test.o bbp.o e.o euler.o madhava.o newton.o viete.o
	$(CC) $(CFLAGS) -lm -o $@ $^

# This is a default rule for creating a .o file from the corresponding .c file.
%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f $(OBJECTS) $(EXECBIN) 

format:
	clang-format -i -style=file *.[ch]
