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

int poly_degree(poly * a) {
	int i;
	for (i=MAXS; i>=0; i++) {
		if(a->quof[i].num!=0) return i;
	}
	return -1; //polinomio 0
}

void print_poly(poly * a) {
     int i;
	 if (poly_degree(a)==-1) {
		print("0\n");
		return;
	 }
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

void div_poly(poly * a, poly * b, poly * c) { // c=a/b
	poly resto, tmp2;
	fract tmp, tmp1, tmp3;
	int i, j, k, g;
	init_poly(&resto);
	init_poly(&tmp2);
	init_poly(c);
	init_fract(&tmp);
	for (i=0; i<=MAXS; i++) {
		tmp2.quof[i].num = a->quof[i].num;
		tmp2.quof[i].den = a->quof[i].den;
		tmp2.quof[i].pos = a->quof[i].pos;
	}
	for (g=MAXS; g>=0; g--) {
		if (b->quof[g].num!=0) break;
	}
	while(1) {
		for (k=MAXS; k>=0; k--) {
			if (tmp2.quof[k].num!=0) break;
		}
		if (k<g) break;
		div_fract(&(tmp2.quof[k]), &(b->quof[g]), &tmp);
		c->quof[k-g] = tmp;
		for (i=g; i>=0; i--) {
			mult_fract(&(b->quof[i]), &tmp, &tmp1);
			subtr_fract(&(tmp2.quof[i+k-g]), &tmp1, &(resto.quof[i+k-g]));
		}
		for (i=k; i>=k-g; i--) {
			tmp2.quof[i].num=resto.quof[i].num;
			tmp2.quof[i].den=resto.quof[i].den;
			tmp2.quof[i].pos=resto.quof[i].pos;
		}
	}
	return;
}

void rem_poly(poly * a, poly * b, poly * c) { // a/b
	poly resto, tmp2;
	fract tmp, tmp1, tmp3;
	int i, j, k, g;
	init_poly(&resto);
	init_poly(&tmp2);
	init_poly(c);
	init_fract(&tmp);
	for (i=0; i<=MAXS; i++) {
		tmp2.quof[i].num = a->quof[i].num;
		tmp2.quof[i].den = a->quof[i].den;
		tmp2.quof[i].pos = a->quof[i].pos;
	}
	for (g=MAXS; g>=0; g--) {
		if (b->quof[g].num!=0) break;
	}
	while(1) {
		for (k=MAXS; k>=0; k--) {
			if (tmp2.quof[k].num!=0) break;
		}
		if (k<g) break;
		div_fract(&(tmp2.quof[k]), &(b->quof[g]), &tmp);
		c->quof[k-g] = tmp;
		for (i=g; i>=0; i--) { 
			mult_fract(&(b->quof[i]), &tmp, &tmp1);
			subtr_fract(&(tmp2.quof[i+k-g]), &tmp1, &(resto.quof[i+k-g]));
		}
		for (i=k; i>=k-g; i--) {
			tmp2.quof[i].num=resto.quof[i].num;
			tmp2.quof[i].den=resto.quof[i].den;
			tmp2.quof[i].pos=resto.quof[i].pos;
		}
	}
	for (i=0; i<=MAXS; i++) {
			c->quof[i].num=tmp2.quof[i].num;
			c->quof[i].den=tmp2.quof[i].den;
			c->quof[i].pos=tmp2.quof[i].pos;
	}
	return;
}

//EU ESTOU AQUI AQUI
void factor_poly(poly * a) {
	int fst, lst, i,j,k;
	fract sum, tmpsum1, tmpsum2;
	poly tmp, tmp1;
	init_poly(&tmp);
	init_poly(&tmp1);
	if (poly_degree(a)==0) {
		print("(%i)\n", a->quof[0]);
		return;
	}
	if (poly_degree(a)==-1) {
		return;
	}
	if (a->quof[0].num==0) {
		print("(x)");
		tmp.quof[1].num=1;
		tmp.quof[1].den=1;
		tmp.quof[1].pos=1;
		div_poly(a, &tmp, &tmp1);
		if (poly_degree(&tmp1)>=0) {
			factor_poly(&tmp1);
			return;
		} else {
			print ("\n");
			return;
		}	
	}
	for (i=0; i<MAXS && a->quof[i].num==0; i++); 
	fst=i;
	for (i=MAXS; i>=0 && a->quof[i].num==0; i--);
	lst=i;
	tmp.quof[0].den=1;
	tmp.quof[0].num=x_lcm(a->quof[fst].den, a->quof[lst].den);
	tmp.quof[0].pos=1;
	if (tmp.quof[0].num!=1) {
		if(a->quof[lst].pos==-1) {
			tmp.quof[0].pos=-1;
			print("(-(1/%i))", tmp.quof[0].num);
		} else {
			print("(1/%i)", tmp.quof[0].num);
		}
	} else {
		if(a->quof[lst].pos==-1) {
			tmp.quof[0].pos=-1;
			print("(-1)");
		}
	}
	mult_poly(a, &tmp, &tmp1);
	init_fract(&sum);
	for (i=1; i<=tmp1.quof[fst].num; i++) {
		if (tmp1.quof[fst].num%i==0) {
			for (j=1; j<=tmp1.quof[lst].num; j++) { 
				if (tmp1.quof[lst].num%j==0) {
					init_fract(&sum);                  
					for (k=0; k<MAXS; k++) {
						init_fract(&tmpsum1);
						init_fract(&tmpsum2);
						tmpsum1.num=i;
						tmpsum1.den=j;
						tmpsum1.pos=1;
						simp_fract(&tmpsum1);
						pow_fract(&tmpsum1, k);
						mult_fract(&tmpsum1, &(tmp1.quof[k]), &tmpsum2);
						add_fract(&sum, &tmpsum2, &tmpsum1);
						sum.num = tmpsum1.num;
						sum.den = tmpsum1.den;
						sum.pos = tmpsum1.pos;
					}
					if (sum.num==0) {
						tmp.quof[1].num=1;
						tmp.quof[1].den=1;
						tmp.quof[1].pos=1;
						tmp.quof[0].num=i;
						tmp.quof[0].den=j;
						tmp.quof[0].pos=-1;
						simp_fract(&tmp.quof[0]);
						div_poly(&tmp1,&tmp, a);
						if (tmp.quof[0].den==1) {
							if(tmp.quof[0].pos==-1) {
								print("(x+%i)", tmp.quof[0].num);
							} else if(tmp.quof[0].pos==1) {
								print("(x-%i)", tmp.quof[0].num);
							}
						} else if(tmp.quof[0].num==0) {
							print("(x)");
						} else {
							if(tmp.quof[0].pos==-1) {
								print("(x+(%i/%i))", tmp.quof[0].num, tmp.quof[0].den);
							} else if(tmp.quof[0].pos==1) {
								print("(x-%i)", tmp.quof[0].num, tmp.quof[0].den);
							}
						}
						
						if (poly_degree(a)>=0) {
							factor_poly(a);
							return;
						} else {
							print ("\n");
							return;
						}						
						
					}
				}
				if (tmp1.quof[lst].num%j==0) {
					init_fract(&sum);                  
					for (k=0; k<MAXS; k++) {
						init_fract(&tmpsum1);
						init_fract(&tmpsum2);
						tmpsum1.num=i;
						tmpsum1.den=j;
						tmpsum1.pos=-1;
						simp_fract(&tmpsum1);
						pow_fract(&tmpsum1, k);
						mult_fract(&tmpsum1, &(tmp1.quof[k]), &tmpsum2);
						add_fract(&sum, &tmpsum2, &tmpsum1);
						sum.num = tmpsum1.num;
						sum.den = tmpsum1.den;
						sum.pos = tmpsum1.pos;
					}
					if (sum.num==0) {
						tmp.quof[1].num=1;
						tmp.quof[1].den=1;
						tmp.quof[1].pos=1;
						tmp.quof[0].num=i;
						tmp.quof[0].den=j;
						tmp.quof[0].pos=1;
						simp_fract(&tmp.quof[0]);
						div_poly(&tmp1,&tmp, a);
						if (tmp.quof[0].den==1) {
							if(tmp.quof[0].pos==-1) {
								print("(x+%i)", tmp.quof[0].num);
							} else if(tmp.quof[0].pos==1) {
								print("(x-%i)", tmp.quof[0].num);
							}
						} else if(tmp.quof[0].num==0) {
							print("(x)");
						} else {
							if(tmp.quof[0].pos==-1) {
								print("(x+(%i/%i))", tmp.quof[0].num, tmp.quof[0].den);
							} else if(tmp.quof[0].pos==1) {
								print("(x-%i)", tmp.quof[0].num, tmp.quof[0].den);
							}
						}
						
						if (poly_degree(a)>=0) {
							factor_poly(a);
							return;
						} else {
							print ("\n");
							return;
						}						
						
					}
				}
			}
		}
	}
	print("(");
	print_poly(a);
	//aplly wikipedia's method to a simplified equation(reduces complexity)
	//TD
	return;
}

//TD:
void solvepoly(poly * a, poly * b) { //x: a(x)=b(x)
	int i;
	poly c;
	init_poly(&c);
	subtr_poly(a,b,&c); //a=b <=> a-b=0 <=> c=0
	print_poly(&c);
	print("=0 <=>\n");
	print ("<=> ");
	
}                              

void pow_poly(poly * a, poly * b, poly * c);
#endif