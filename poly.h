#include "stdio.h"
#include "fract.h"
#define MAXS 100


typedef struct {
    int quof[MAXS+1]; //os quoficientes por ordem: quof[0]-> x^0, ...    quof[50] // existem 100 para evitar conflitos com a multiplicacao e divisao   
}poly ;

void init_poly(poly * a) {
     int i;
     for (i=0; i<=MAXS; i++) {
         a->quof[i]=0;    
     }
     return;
}

void print_poly(poly * a) {
     int i;
     for (i=MAXS-1; i>1; i--) {
         if (a->quof[i]!=0) {
			if (a->quof[i] >= 0) printf("+");
			if (a->quof[i]==1) printf("x^%d", i);
			else if (a->quof[i]==-1) printf("-x^%d", i);
			else printf("%dx^%d", a->quof[i], i);                
         }
     }
	 if (a->quof[1]!=0) {
		if (a->quof[1] >= 0) printf("+");
		if (a->quof[1]==1) printf("x");
		else if (a->quof[1]==-1) printf("-x");
		else printf("%dx", a->quof[1]);
	 }
	 if (a->quof[0]>=0) printf("+");
     printf("%d", a->quof[0]);                 
     printf("\n");
}

void add_poly(poly * a, poly * b, poly * c) { //c=a+b
     int i;
     for (i=0; i<MAXS; i++) {
         c->quof[i] = a->quof[i] + b->quof[i];
     }
     return;
}

void subtr_poly(poly * a, poly * b, poly * c) { //c= a-b
     int i;
     for (i=0; i<MAXS; i++) {
         c->quof[i] = a->quof[i] - b->quof[i];
     }
     return;
}

void simetric_poly(poly * a) {
	int i;
	for (i=0; i<MAXS; i++) {
         a->quof[i] = - a->quof[i];
     }
     return;
}
void mult_poly(poly * a, poly * b, poly * c) { //c e o local a armazenar a variavel
     int i, j;
     init_poly(c);
     for (i=0; i<((MAXS+1)/2); i++) {
         for (j=0; j<((MAXS+1)/2); j++) {
             c->quof[i+j] += a->quof[i] * b->quof[j];  
         }
     }
     return;
}