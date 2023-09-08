/* See LICENSE file for copyright and license details. */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "qnum.h"

extern qnum btoq(const char *nptr, int base);
extern const char *qtob(qnum numb, int base);

static void die(void)
{
	perror(NULL);
	exit(errno);
}

/* Convert number from any base to any base. */
int main(int argc, char **argv)
{
	qnum n;
	const char *s = argv[1];

	errno = 0;

	if (argc != 4) {
		fprintf(stderr, "Usage: qconv str base base\n");
		exit(1);
	}

	n = btoq(s, atoi(argv[2]));
	if (errno != 0)
		die();

	s = qtob(n, atoi(argv[3]));
	if (errno == EINVAL)
		die();

	puts(s);
	exit(0);
}
