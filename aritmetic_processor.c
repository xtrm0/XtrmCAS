#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "poly.h"


//Estou aqui
int read_num(int start, char a[]) {

}

void read_poly(poly * a, char inputz[1000]) {
	int i, k;
	char num1[32]="", num2[32]="", num3[32]="";
	init_poly(a);
	k=0;
	for (i=0; (unsigned)i<strlen(inputz); i++) {
		
	}
	
}

int main() {
    int N;
    poly a, b, c;
    init_poly(&a);
    a.quof[0]=1; a.quof[1]=-2;
    init_poly(&b);
    b.quof[0]=1; b.quof[1]=2;
    mult_poly(&a, &b, &c);
    print_poly(&c);
    //Quando o programa ler um P, significa que entre os proximos parentesis: 
	//    1) nao havera outros parentesis
	//    2) existe um polinomio
    scanf("%d", &N);
    return 0;
}
