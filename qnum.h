/* See LICENSE file for copyright and license details. */
typedef struct {
	long num;
	long den;
} qnum;

void qnum_reduce(qnum *q);
