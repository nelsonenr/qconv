#include <stdlib.h>

#include "qnum.h"

static long gcd(long a, long b)
{
	while (b != 0) {
		a %= b;
		if (a == 0)
			return b;
		b %= a;
	}

	return a;
}

void qnum_reduce(qnum *q)
{
	long d = labs(gcd(q->num, q->den));

	q->num /= d;
	q->den /= d;
}
