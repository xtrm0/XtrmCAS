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
     for (i=MAXS-1; i>0; i--) {
         if (a->quof[i]!=0) {
            printf("%d*x^%d + ", a->quof[i], i);                 
         }
     }
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