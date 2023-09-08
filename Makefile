# See LICENSE file for copyright and license details.
SRC = main.c qtob.c btoq.c qnum.c
OBJ = ${SRC:.c=.o}

BINDIR = /usr/local/bin
CFLAGS = -std=c89 -O2 -Wall -pedantic

all: qconv

.c.o:
	gcc -c ${CFLAGS} $<

${OBJ}: qnum.h Makefile

qconv: ${OBJ}
	gcc -o $@ $^

install: qconv
	mkdir -p ${BINDIR}
	cp -f qconv ${BINDIR}
	chmod 755 ${BINDIR}/qconv

uninstall:
	rm -f ${BINDIR}/qconv

clean:
	rm -f qconv ${OBJ}

.PHONY: all clean install
