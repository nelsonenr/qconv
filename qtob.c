#include <limits.h>

#include "qnum.h"

static char buf[72];
static char *endc = buf + sizeof(buf) - 1;

static char itoc(register int i)
{
	if (0 <= i && i <= 9)
		return i + '0';
	if (9 < i && i <= 35)
		return i + 'a' - 10;
	return '\0';
}

const char *qtob(qnum n, int b)
{
	int neg;
	long ip;
	char *s = endc, *t = buf;

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
	}

	*t = '\0';

	return buf;
}
