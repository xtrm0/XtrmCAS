#ifndef _AP
#define _AP
#include <string.h>
#include <math.h>
#include "poly.h"

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
	for (; (unsigned)i<strlen(a); i++) {
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
	fract tmp1, tmp2;
	init_poly(a);
	init_fract(&tmp1);
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
				init_fract(&tmp1);
				tmp1.den=1;
				if (n1<0) {tmp1.pos=-1; n1=-n1;}
				tmp1.num=n1;
				if (n1==0) tmp1.den=0;
				add_fract(&tmp1, &(a->quof[n2]), &tmp2);
				a->quof[n2] = tmp2;
			} else {
				init_fract(&tmp1);
				tmp1.den=1;
				if (n1<0) {tmp1.pos=-1; n1=-n1;}
				tmp1.num=n1;
				if (n1==0) tmp1.den=0;
				add_fract(&tmp1, &(a->quof[1]), &tmp2);
				a->quof[1] = tmp2;
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
					init_fract(&tmp1);
					tmp1.den=1;
					if (n1<0) {tmp1.pos=-1; n1=-n1;}
					tmp1.num=n1;
					if (n1==0) tmp1.den=0;
					add_fract(&tmp1, &(a->quof[n2]), &tmp2);
					a->quof[n2] = tmp2;
				} else {
					init_fract(&tmp1);
					tmp1.den=1;
					if (n1<0) {tmp1.pos=-1; n1=-n1;}
					tmp1.num=n1;
					if (n1==0) tmp1.den=0;
					add_fract(&tmp1, &(a->quof[1]), &tmp2);
					a->quof[1] = tmp2;
				}
			} else {
				init_fract(&tmp1);
				tmp1.den=1;
				if (n1<0) {tmp1.pos=-1; n1=-n1;}
				tmp1.num=n1;
				if (n1==0) tmp1.den=0;
				add_fract(&tmp1, &(a->quof[0]), &tmp2);
				a->quof[0] = tmp2;
			}
		}
	}
	
}

int programa() {
	int xd=1;
	poly a, b ,c;
	int i;
	int st;
	int pars=0;
	char input[1000];
	init_poly(&a); init_poly(&b); init_poly(&c);
	input[0]=0;
	input[0]=getchar();
	while (input[xd-1]!='\n') {
		input[xd]=getchar();
		xd++;
		input[xd]=0;
	}
	if (input[0]=='q' || input[0]=='Q') return 0; //exit
	if (input[0]=='*') {
		for (i=1; (unsigned)i<strlen(input); i++) {
			if (input[i]=='(') {
				pars++;
			}
			if (input[i]==')') {
				if (pars==0) {
					print("Erro: parentesis\n");
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
		for (i=i+1; (unsigned)i<strlen(input); i++) {
			if (input[i]=='(') {
				pars++;
			}
			if (input[i]==')') {
				if (pars==0) {
					print("Erro: parentesis\n");
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
	if (input[0]=='-') {
				for (i=1; (unsigned)i<strlen(input); i++) {
			if (input[i]=='(') {
				pars++;
			}
			if (input[i]==')') {
				if (pars==0) {
					print("Erro: parentesis\n");
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
		for (i=i+1; (unsigned)i<strlen(input); i++) {
			if (input[i]=='(') {
				pars++;
			}
			if (input[i]==')') {
				if (pars==0) {
					print("Erro: parentesis\n");
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
			for (i=1; (unsigned)i<strlen(input); i++) {
			if (input[i]=='(') {
				pars++;
			}
			if (input[i]==')') {
				if (pars==0) {
					print("Erro: parentesis\n");
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
		for (i=i+1; (unsigned)i<strlen(input); i++) {
			if (input[i]=='(') {
				pars++;
			}
			if (input[i]==')') {
				if (pars==0) {
					print("Erro: parentesis\n");
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
	} else if (input[0]=='R' || input[0]=='r') {
		for (i=1; (unsigned)i<strlen(input); i++) {
			if (input[i]=='(') {
				pars++;
			}
			if (input[i]==')') {
				if (pars==0) {
					print("Erro: parentesis\n");
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
		for (i=i+1; (unsigned)i<strlen(input); i++) {
			if (input[i]=='(') {
				pars++;
			}
			if (input[i]==')') {
				if (pars==0) {
					print("Erro: parentesis\n");
					return -1;
				}
				pars--;
				if (pars==0) {
					break;
				}
			}
		}
		read_poly(&b, input, st, i-1);
		rem_poly(&a, &b, &c);
		print_poly(&c);
		return 1;
	}else if (input[0]=='/') {
		for (i=1; (unsigned)i<strlen(input); i++) {
			if (input[i]=='(') {
				pars++;
			}
			if (input[i]==')') {
				if (pars==0) {
					print("Erro: parentesis\n");
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
		for (i=i+1; (unsigned)i<strlen(input); i++) {
			if (input[i]=='(') {
				pars++;
			}
			if (input[i]==')') {
				if (pars==0) {
					print("Erro: parentesis\n");
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
	}else if (input[0]=='F') {
		for (i=1; (unsigned)i<strlen(input); i++) {
			if (input[i]=='(') {
				pars++;
			}
			if (input[i]==')') {
				if (pars==0) {
					print("Erro: parentesis\n");
					return -1;
				}
				pars--;
				if (pars==0) {
					break;
				}
			}
		}
		read_poly(&a, input, 2, i-1);
		factor_poly(&a);
		return 1;
	}
	print("nao foi possivel processar o input\n");
	return 2;
}
void doloop() {
	int N;
	while (programa()>0);
    return;
}
#endif