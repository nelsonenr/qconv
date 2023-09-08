/* See LICENSE file for copyright and license details. */
#include <errno.h>
#include <limits.h>

#include "qnum.h"

static char buf[72];
static char *endc = buf + sizeof(buf) - 1;

/* Convert integer i to character. */
static char itoc(register int i)
{
	if (0 <= i && i <= 9)
		return i + '0';
	if (9 < i && i <= 35)
		return i + 'a' - 10;
	return '\0';
}

/* Convert fraction n to string in base b. */
const char *qtob(qnum n, int b)
{
	int neg;
	long ip;
	char *s = endc, *t = buf;

	if (!(2 <= b && b <= 36) || n.den == 0) {
		errno = EINVAL;
		return (char *) 0;
	}

	qnum_reduce(&n);
	if ((neg = n.num < 0))
		n.num = -n.num;

	ip = n.num / n.den;
	do {
		*--s = itoc(ip % b);
	} while ((ip /= b));
	if (neg)
		*--s = '-';

	while (s < endc)
		*t++ = *s++;

	n.num %= n.den;
	if (n.den > 1 && n.num < LONG_MAX / b) {
		*t++ = '.';
		do {
			n.num = n.num * b;
			qnum_reduce(&n);
			*t++ = itoc((n.num / n.den) % b);
		} while (n.den > 1 && n.num < LONG_MAX / b && t < endc);
		if (n.num > 1)
			errno = ERANGE;
	}

	*t = '\0';

	return buf;
}
