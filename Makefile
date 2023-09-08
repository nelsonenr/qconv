# See LICENSE file for copyright and license details.
SRC = main.c qtob.c btoq.c qnum.c
OBJ = ${SRC:.c=.o}

CFLAGS = -std=c89 -O2 -Wall -pedantic

all: qconv

.c.o:
	gcc -c ${CFLAGS} $<

${OBJ}: qnum.h Makefile

qconv: ${OBJ}
	gcc -o $@ $^

clean:
	rm -f qconv ${OBJ}
