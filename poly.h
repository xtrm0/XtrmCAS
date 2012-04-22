#ifndef _POLY
#define _POLY
#include "console.h"
#include "fract.h"
#define MAXS 100
//O erro esta neste ficheiro, na parte de multiplicar, a seguir a corrigir, o algoritmo da divisao ja esta feito.

typedef struct {
    fract quof[MAXS+1]; //os quoficientes por ordem: quof[0]-> x^0, ...    quof[50] // existem 100 para evitar conflitos com a multiplicacao e divisao   
}poly ;

void init_poly(poly * a) {
     int i;
	 fract tmp;
	 init_fract(&tmp);
     for (i=0; i<=MAXS; i++) {
         a->quof[i]=tmp;    
     }
     return;
}

void print_poly(poly * a) {
     int i;
     for (i=MAXS-1; i>1; i--) {
         if (a->quof[i].num!=0) {
			if (a->quof[i].pos == 1) print("+");
			else if (a->quof[i].pos == -1) print("-");
			else print("erro");
			if (a->quof[i].den==1) {
				if (a->quof[i].num==1) print("x^%i", i);
				else print("%ix^%i", a->quof[i].num, i);  
			} else {
				print("(%i/%i)x^%i", a->quof[i].num, a->quof[i].den, i);
			}
         }
     }
	 if (a->quof[1].num!=0) {
		if (a->quof[1].pos == 1) print("+");
		else if (a->quof[1].pos == -1) print("-");
		else print("erro");
		if (a->quof[1].den==1) {
			if (a->quof[1].num==1) print("x");
			else print("%ix", a->quof[1].num);  
		} else {
			print("(%i/%i)x", a->quof[1].num, a->quof[1].den);
		}
    }
	if (a->quof[0].num!=0) {
		if (a->quof[0].pos == 1) print("+");
		else if (a->quof[0].pos == -1) print("-");
		else print("erro");
		if (a->quof[0].den==1) {
			print("%i", a->quof[0].num);  
		} else {
			print("(%i/%i)", a->quof[0].num, a->quof[0].den);
		}
    }
	print("\n");
}

void add_poly(poly * a, poly * b, poly * c) { //c=a+b
     int i;
     for (i=0; i<MAXS; i++) {
         add_fract(&(a->quof[i]), &(b->quof[i]), &(c->quof[i]));
     }
     return;
}

void subtr_poly(poly * a, poly * b, poly * c) { //c= a-b
     int i;
     for (i=0; i<MAXS; i++) {
         subtr_fract(&(a->quof[i]), &(b->quof[i]), &(c->quof[i]));
     }
     return;
}

void simetric_poly(poly * a) {
	int i;
	for (i=0; i<MAXS; i++) {
		if(a->quof[i].num!=0)
			a->quof[i].pos = -a->quof[i].pos;
     }
     return;
}
void mult_poly(poly * a, poly * b, poly * c) { //c e o local a armazenar a variavel
     int i, j;
	 fract tmp1, tmp2;
     init_poly(c);
	 init_fract(&tmp1); init_fract(&tmp2);
     for (i=0; i<((MAXS+1)/2); i++) {
         for (j=0; j<((MAXS+1)/2); j++) {
			mult_fract(&(a->quof[i]), &(b->quof[j]), &tmp1);
			add_fract(&tmp1, &(c->quof[i+j]), &tmp2);
            c->quof[i+j].num = tmp2.num;
            c->quof[i+j].den = tmp2.den;
            c->quof[i+j].pos = tmp2.pos;
         }
     }
     return;
}

void div_poly(poly * a, poly * b, poly * c) { // a/b
	poly resto, tmp2;
	fract tmp, tmp1, tmp3;
	int i, j, k, g;
	init_poly(&resto);
	init_poly(c);
	init_fract(&tmp);
	for (g=MAXS; g>=0; g--) {
		if (b->quof[g].num!=0) break;
	}
	while(1) {
		for (k=MAXS; k>=0; k--) {
			if (a->quof[k].num!=0) break;
		}
		if (k<g) break;
		if (k==g && a->quof[k].num==0) break; 
		div_fract(&(a->quof[k]), &(b->quof[g]), &tmp);
		c->quof[k-g] = tmp;
		for (i=g; i>=0; i--) {
			mult_fract(&(b->quof[i]), &tmp, &tmp1);
			subtr_fract(&(a->quof[i+k-g]), &tmp1, &(resto.quof[i+k-g]));
		}
		for (i=0; i<=MAXS; i++) {
			a->quof[i].num=resto.quof[i].num;
			a->quof[i].den=resto.quof[i].den;
			a->quof[i].pos=resto.quof[i].pos;
		}
	}
	return;
}

void pow_poly(poly * a, poly * b, poly * c);
#endif