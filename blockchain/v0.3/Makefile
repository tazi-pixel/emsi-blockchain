CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -ggdb3 -c
SRC=$(wildcard *.c) $(wildcard transaction/*.c)
OBJS=$(SRC:.c=.o)
NAME=libhblk_blockchain.a
.PHONY: clean oclean
clean:
	rm *~ $(NAME)
oclean:
	rm $(OBJS)
libhblk_blockchain.a: blockchain.h $(OBJS)
	ar rcs $(NAME) $(OBJS)
	make oclean
