  
C = gcc
FLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89 -g3
SRC = sha256.c ec_create.c ec_to_pub.c ec_from_pub.c ec_save.c ec_load.c ec_sign.c ec_verify.c
LIBRARY = libhblk_crypto.a
SRCOUTPUT = $(patsubst %.c, %.o, $(SRC))

.PHONY: libhblk_crypto.a

libhblk_crypto.a: $(SRCOUTPUT)
	ar rcs $(LIBRARY) $(SRCOUTPUT)
