#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "matz.h"

typedef struct{
    int num, den;
    int pos;// casos possiveis: -1 -> negativo, 0->0, 1-> positivo, 2->erro
}fract ;
void simp_fract(fract * a){ //c = irreductible(c)
     return;
}

bool isvalid_fract(fract * a) {
    if (a->den == 0 && a->num !=0) return false;
    return true;
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
          print ("Erro: a/0, add_fract");
     }
     if (a->num==0) {
          &c = &b;
          return;
     }
     g = x_lcm(b->den, a->den);
     c->num = (a->num * a->pos * (g / a->den)) + ( b->num * b->pos * (g / b->den));
     
     simp_fract(c);
     return;     
}

void subtr_fract(fract * a, fract * b, fract * c) {
     
}
void mult_fract(fract * a, fract * b, fract * c); //c= a * b
void div_fract(fract * a, fract * b, fract * c); //c= a / b

