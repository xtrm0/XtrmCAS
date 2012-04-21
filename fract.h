#ifndef _FRACT
#define _FRACT
#include <string.h>
#include <math.h>
#include "matz.h"

typedef struct{
    int num, den;
    int pos;// casos possiveis: -1 -> negativo, 1-> positivo, 2->erro
}fract ;

void simp_fract(fract * a){ //c = irreductible(c)
    int g;
	g = x_gcd(a->num, a->den);
    a->num = ((a->num) / g);
	a->den = ((a->den) / g);
    return;
}

int isvalid_fract(fract * a) {
    if (a->den == 0 && a->num !=0) return 0;
	if (a->pos == 2) return 0;
    return 1;
}

void init_fract(fract * c) {
     c->den=0;
     c->num=0;
     c->pos=1;
     return;     
}

void add_fract(fract * a, fract * b, fract * c) {
     int g;
     init_fract(c);
     if (!(isvalid_fract(a) && isvalid_fract(b))) {
        c->pos = 2;
        print("Erro: a/0, add_fract");
		return;
     }
     if (a->num==0) {
          c->den = b->den;
          c->num = b->num;
          c->pos = b->pos;
          return;
     }
     if (b->num==0) {
          c->den = a->den;
          c->num = a->num;
          c->pos = a->pos;
          return;
     }
     g = x_lcm(b->den, a->den);
     c->num = (a->num * a->pos * (g / a->den)) + ( b->num * b->pos * (g / b->den));
     c->den = g;
     if (c->num < 0) {
        c->num = -c->num;           
        c->pos = -1;
     }
     simp_fract(c);
     return;     
}

void subtr_fract(fract * a, fract * b, fract * c) {
     b->pos = b->pos * -1;
     add_fract(a, b, c);
	 b->pos = b->pos * -1;
     return;
}

void mult_fract(fract * a, fract * b, fract * c) {
	 c->den = a->den * b->den;
     c->num = a->num * b->num;
     c->pos = a->pos * b->pos;
	 if (a->num==0 || b->num==0) {
		c->pos = 1;
		c->den = 0;
	 }
	 if (!(isvalid_fract(a) && isvalid_fract(b))) {
        c->pos = 2;
        print("Erro: a/0, mult_fract");
     }
     simp_fract(c);
     return;
}

void div_fract(fract * a, fract * b, fract * c){
     c->den = a->den * b->num;
     c->num = a->num * b->den;
     c->pos = a->pos * b->pos; 
	 if(c->den==0) {
		print("indefenido");
		return;
	 }
	 if(c->num==0) {
		c->den=0;
		c->pos=1;
		return;
	 }
     simp_fract(c);
     return;
}
#endif
