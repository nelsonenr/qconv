/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <stdlib.h>

#include "qnum.h"

extern qnum btoq(const char *nptr, int base);
extern const char *qtob(qnum numb, int base);

/* Convert number from any base to any base. */
int main(int argc, char **argv)
{
	qnum n;
	const char *s = argv[1];

	if (argc != 4) {
		fprintf(stderr, "Usage: qconv str base base\n");
		exit(1);
	}

	n = btoq(s, atoi(argv[2]));
	s = qtob(n, atoi(argv[3]));

	puts(s);
	exit(0);
}
