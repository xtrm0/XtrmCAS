#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "poly.h"
//Nota, o programa nao devera ter espacos no input, para evitar qualquer tipo de erros.
//Falta a funcao para parentesear o input, e acabar a interpreta onde MARCADO

int read_num(int i, char a[]) {
	char number[30]="";
	int k=0;
	if (a[i] == '-' || a[i] == '+') {
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

void read_poly(poly * a, char inputz[], int st, int en) {

	int i, n1, n2;
	init_poly(a);
	
	for (i=st; i<=en; i++) {
		if (inputz[i]=='x') {
			a->quof[1] += 1;
			continue;
		}
		if (inputz[i+1]=='x') {
			a->quof[1] -= 1;
			continue;
		}
		n1 = read_num(i, inputz);
		i+=  ((n1==0) ? (1) : ((int) (floor( log10( abs( n1 ) ) ) + 1)));
		if (n1<0) i++;
		if (inputz[i]=='*') {
			i+=2;
			if (inputz[i]=='^') {
				i++;
				n2 = read_num(i, inputz);
				i+=((n1==0) ? (1) : ((int) (floor( log10( abs( n1 ) ) ) + 1)));
				a->quof[n2] += n1;
			} else {
				a->quof[1] += n1;
			}
		} else {
			a->quof[0] += n1;
		}
	}
	
}

//Estou aqui
poly interpreta(char in[], int st, int en) {
	poly ret;
	int i, par=0;
	bool hasp;
	int newst, newen;
	init_poly(&ret);
	for (i=st; i<=en; i++) {
		if (in[i]=='(') {
			hasp=true;
			if (par==0) {
				newst = i+1;
			}
			par++;
		}
		if (in[i]==')') {
			if (par==0) {
				printf("Erro: input mal formatado, interpreta");
			}
			par--;
			if (par==0) {
				newen = i-1;
				ret = interpreta(in, newst, newen);
				i++;
				break;
			}
		}
	}
	//MARCADO
	if (hasp==true) {
		return ret;
	} else {
		read_poly(&ret, in, st, en);
		return ret;
	}
	
}
int main() {
    int N;
    int a;
	char input[1000] = "-123";
	char input2[1000] = "+123";
	char input3[1000] = "0123309";
    a = read_num(0, input);
	printf("%d\n", a);
    a = read_num(0, input2);
	printf("%d\n", a);
    a = read_num(0, input3);
	printf("%d\n", a);
	
    //Quando o programa ler um P, significa que entre os proximos parentesis: 
	//    1) nao havera outros parentesis
	//    2) existe um polinomio
    scanf("%d", &N);
    return 0;
}
