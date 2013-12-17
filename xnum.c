#include "xnum.h"

void num_init(num *c) {
	c->val = 0;
	c->signal = 1;
}

void num_init_d(num *c, int a) {
	c->val=iabs(a);
	c->signal = ((a>=0) ? 1 : -1);
}

void num_copy(num *a, num *c)  {
	c->val = a->val;
	c->signal = a->signal;
}

void num_add(num *a, num *b, num *c) {
	if (a->signal * b->signal == 1) {
		c->val = a->val + b->val;
		c->signal = a->signal;
	} else {
		c->val = a->val - b->val;
		c->signal = ((a->val >= b->val) ? a->signal : -a->signal);
	}
}

void num_sub(num *a, num *b, num *c) {
	if (a->signal * b->signal == 1) {
		c->val = a->val - b->val;
		c->signal = ((a->val >= b->val) ? a->signal : -a->signal);
	} else {
		c->val = a->val + b->val;
		c->signal = a->signal;
	}
}

void num_mult(num *a, num *b, num *c) {
	c->val = a->val * b->val;
	c->signal = ((c->val==0) ? 1 : a->signal * b->signal);
}



void num_print(num *a) {
	//TODO connect this to console.c
	printf("%d", a->val);
}