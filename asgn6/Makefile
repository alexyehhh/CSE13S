CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: encode decode

encode: encode.o trie.o word.o io.o
	$(CC) $(CFLAGS) -o $@ $^

decode: decode.o trie.o word.o io.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f encode decode *.o

format:
	clang-format -i -style=file *.[ch]
