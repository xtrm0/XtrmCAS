#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "poly.h"
//Nota, o programa tera de cortar todos os espacos, para evitar qualquer tipo de erros.

//Estou aqui
int read_num(int i, char a[]) {
	char number[30]="";
	int k=0;
	if (number[0] == '-' || number[0] == '+') {
		number[0] = a[i];
		k++; 
		i++;
	}
	for (; unsigned(i)<strlen(a); i++) {
		if (a[i]>='0' && a[i]<='9') {
			number[k] = a[i];
			k++;
			number[k]=0;
		} else {
			return atoi(number);
		}
	}
	return atoi(number);
}

void read_poly(poly * a, char inputz[1000]) {
	int i, n1, n2;
	init_poly(a);
	
	for (i=0; (unsigned)i<strlen(inputz); i++) {
		if (inputz[i]=='x') {
			a->quof[1] += 1;
			continue;
		}
		if (inputz[i+1]=='x') {
			a->quof[1] -= 1;
			continue;
		}
		n1 = read_num(i, inputz);
		i+=(int) (floor( log10( abs( n1 ) ) ) + 1);
		if (n1<0) i++;
		if (inputz[i]=='*') {
			i+=2;
			if (inputz[i]=='^') {
				i++;
				n2 = read_num(i, inputz);
				i+=(int) (floor( log10( abs( n2 ) ) ) + 1);
				a->quof[n2] += n1;
			} else {
				a->quof[1] += n1;
			}
		} else {
			a->quof[0] += n1;
		}
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
