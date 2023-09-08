/* See LICENSE file for copyright and license details. */
#include <errno.h>
#include <limits.h>

#include "qnum.h"

/* Convert character c to integer. */
static int ctoi(register char c)
{
	if ('0' <= c && c <= '9')
		return c - '0';
	if ('a' <= c && c <= 'z')
		return c - 'a' + 10;
	return INT_MAX;
}

/* Convert string s in base b to fraction. */
qnum btoq(const char *s, int b)
{
	int sign, dot, i = INT_MAX;
	qnum n = {0, 1};

	if (!(2 <= b && b <= 36)) {
		errno = EINVAL;
		return n;
	}

	while (*s == ' ' || *s == '\t')
		++s;

	sign = (*s == '-') ? -1 : 1;
	if (*s == '-' || *s == '+')
		++s;

	for (dot = 0; *s; ++s) {
		if (*s == '.' && !dot) {
			dot = 1;
			continue;
		}
		if (n.num >= LONG_MAX / b) {
			errno = ERANGE;
			break;
		}
		if ((i = ctoi(*s)) >= b)
			break;
		n.num = n.num * b + i;
		if (dot) {
			if (n.den >= LONG_MAX / b)
				break;
			n.den = n.den * b;
			qnum_reduce(&n);
		}
	}

	if (i == INT_MAX)
		errno = EINVAL;

	n.num = n.num * sign;

	return n;
}
