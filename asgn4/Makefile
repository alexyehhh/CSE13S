EXECBIN  = life
CC       = clang
CFLAGS   = -Wall -Wpedantic -Werror -Wextra -Ofast -g -gdwarf-4
LFLAGS   = -lncurses

# All available source .c files are included as SOURCES
SOURCES  = $(wildcard *.c)

# Each .c file has a corresponding .o file
OBJECTS  = $(SOURCES:%.c=%.o)

# These are "phony" targets: they're not real files
.PHONY: all clean format

all: $(EXECBIN)

life: life.o universe.o
	$(CC) -o $@ $^ $(LFLAGS)

# This is the default rule for creating .o files from .c files
%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXECBIN) $(OBJECTS)

format:
	clang-format -i -style=file *.[ch]
