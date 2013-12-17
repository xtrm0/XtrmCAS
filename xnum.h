#ifndef XNUM_H
#define XNUM_H
#include "xmath.h"

/* STUFF FOR BIGINT */
#define MAX_COL 100000000
typedef long long int lli;


typedef struct num {
	lli valz[100];
	int right;
	int val;
	int signal; //plus or minus 1
} num;


/* c = 0 */
void num_init(num *c);
/* c = a */
void num_init_d(num *c, int a);
/* prints a */
void num_print(num *a);
/* c = a */
void num_copy(num *a, num *c);


/* c = a + b */
void num_add(num *a, num *b, num *c);
/* c = a - b */
void num_sub(num *a, num *b, num *c);
/* c = a * b */
void num_mult(num *a, num *b, num *c);

#endif