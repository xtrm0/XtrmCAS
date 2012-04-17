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
	if (a[i]=='x') return 1;
	if (a[i] == '+') {
		number[0] = a[i];
		k++; 
		i++;
		if (a[i]=='x') {
			return 1;
		}
	} else if (a[i] == '-') {
		number[0] = a[i];
		k++; 
		i++;
		if (a[i]=='x') {
			return -1;
		}
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
	
	for (i=st; i<=en;) {
		n1 = read_num(i, inputz);
		if(inputz[i]=='+' || inputz[i]=='-') {
			i++;
		}
		while(inputz[i]>='0' && inputz[i]<='9') i++;
		if (inputz[i]=='*') {
			i+=2;
			if (inputz[i]=='^') {
				i++;
				n2 = read_num(i, inputz);
				if(inputz[i]=='+' || inputz[i]=='-') {
					i++;
				}	
				while(inputz[i]>='0' && inputz[i]<='9') i++;
				a->quof[n2] += n1;
			} else {
				a->quof[1] += n1;
			}
		} else {
			if(inputz[i]=='x') {
				i++;
				if (inputz[i]=='^') {
					i++;
					n2 = read_num(i, inputz);
					if(inputz[i]=='+' || inputz[i]=='-') {
						i++;
					}	
					while(inputz[i]>='0' && inputz[i]<='9') i++;
					a->quof[n2] += n1;
				} else {
					a->quof[1] += n1;
				}
			} else {
				a->quof[0] += n1;
			}
		}
	}
	
}

/*
poly interpreta(char in[], int st, int en) {
	//casos notaveis: /(-x*2)/, /((x*2))/, /(x)/
	poly ret;
	poly tmpa;
	int i, j, par=0;
	bool hasp;
	int newst, newen;
	init_poly(&ret);
	if (in[st]=='(' || in[st+1]=='(') {
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
					printf("Erro: input mal formatado, interpreta, entre: %d, %d", st, en);
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
		if (par!=0) {
			printf("Erro: input mal formatado, interpreta, entre: %d, %d", st, en);
			return ret;
		}
		if (in[st]=='-') {
			ret = simetric_poly(&ret);
		}
	}
	j=newen+2;
	//MARCADO
	if (hasp==true) {
		if (j>=en return true;
		st = newen+2;
		for (j=st; j<=en; j++) {
			
		}
		
	} else {
		read_poly(&ret, in, st, en);
		return ret;
	}
	
}
// */
int programa() {
	poly a, b ,c;
	init_poly(&a); init_poly(&b); init_poly(&c);
	int i;
	int st;
	int pars=0;
	char input[1000];
	scanf("%s", input);
	if (input[0]=='q' || input[0]=='Q') return 0; //exit
	if (input[0]=='*') {
		for (i=1; unsigned(i)<strlen(input); i++) {
			if (input[i]=='(') {
				pars++;
			}
			if (input[i]==')') {
				if (pars==0) {
					printf("Erro: parentesis");
					return -1;
				}
				pars--;
				if (pars==0) {
					break;
				}
			}
		}
		read_poly(&a, input, 2, i-1);
		st=i+2;
		for (i=i+1; unsigned(i)<strlen(input); i++) {
			if (input[i]=='(') {
				pars++;
			}
			if (input[i]==')') {
				if (pars==0) {
					printf("Erro: parentesis");
					return -1;
				}
				pars--;
				if (pars==0) {
					break;
				}
			}
		}
		read_poly(&b, input, st, i-1);
		mult_poly(&a, &b, &c);
		print_poly(&c);
		return 1;
	} else
/*	if (input[0]=='/') {
			for (i=1; unsigned(i)<strlen(input); i++) {
			if (input[i]=='(') {
				pars++;
			}
			if (input[i]==')') {
				if (pars==0) {
					printf("Erro: parentesis");
					return -1;
				}
				pars--;
				if (pars==0) {
					break;
				}
			}
		}
		read_poly(&a, input, 2, i-1);
		st=i+2;
		for (i=i+1; unsigned(i)<strlen(input); i++) {
			if (input[i]=='(') {
				pars++;
			}
			if (input[i]==')') {
				if (pars==0) {
					printf("Erro: parentesis");
					return -1;
				}
				pars--;
				if (pars==0) {
					break;
				}
			}
		}
		read_poly(&b, input, st, i-1);
		div_poly(&a, &b, &c);
		print_poly(&c);
		return 1;
	} else // */
	if (input[0]=='-') {
				for (i=1; unsigned(i)<strlen(input); i++) {
			if (input[i]=='(') {
				pars++;
			}
			if (input[i]==')') {
				if (pars==0) {
					printf("Erro: parentesis");
					return -1;
				}
				pars--;
				if (pars==0) {
					break;
				}
			}
		}
		read_poly(&a, input, 2, i-1);
		st=i+2;
		for (i=i+1; unsigned(i)<strlen(input); i++) {
			if (input[i]=='(') {
				pars++;
			}
			if (input[i]==')') {
				if (pars==0) {
					printf("Erro: parentesis");
					return -1;
				}
				pars--;
				if (pars==0) {
					break;
				}
			}
		}
		read_poly(&b, input, st, i-1);
		subtr_poly(&a, &b, &c);
		print_poly(&c);
		return 1;
	} else
	if (input[0]=='+') {
			for (i=1; unsigned(i)<strlen(input); i++) {
			if (input[i]=='(') {
				pars++;
			}
			if (input[i]==')') {
				if (pars==0) {
					printf("Erro: parentesis");
					return -1;
				}
				pars--;
				if (pars==0) {
					break;
				}
			}
		}
		read_poly(&a, input, 2, i-1);
		st=i+2;
		for (i=i+1; unsigned(i)<strlen(input); i++) {
			if (input[i]=='(') {
				pars++;
			}
			if (input[i]==')') {
				if (pars==0) {
					printf("Erro: parentesis");
					return -1;
				}
				pars--;
				if (pars==0) {
					break;
				}
			}
		}
		read_poly(&b, input, st, i-1);
		add_poly(&a,&b, &c);
		print_poly(&c);
		return 1;
	}
	//else
	return -1;
}
int main() {
	int N;
	while (programa()>0);
	
    //Quando o programa ler um P, significa que entre os proximos parentesis: 
	//    1) nao havera outros parentesis
	//    2) existe um polinomio
    scanf("%d", &N);
    return 0;
}
