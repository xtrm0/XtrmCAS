#include "poly.h" //my polynomials class, /
//this method is based on the fact that all real rational roots must be in the form (a/b), where a is a divisor
//of the the highest rank poly, and b is a divisor of the lowest rank one.
//After that we know that the remaining root are irrational, and we use some method, such as that described in
//this page to solve, or to aproximate roots: (http://en.wikipedia.org/wiki/Root-finding_algorithm#Algorithm)

double x_pow(double a, int b) {
	int i;
	double ans=a;
	if (b==0) return 1;
	for (i=1; i<b; i++) {
		ans = a*ans;
	}
	return ans;
}
void printandfind(poly * a) {
	int fst, lst, i,j,k;
	double sum;
	for (i=0; i<MAXS && a->quof[i]==0; i++); //MAXS is the maximum number of factor as defined in poly.h
	fst=i;
	for (i=MAXS; i>=0 && a->quof[i]==0; i--);
	lst=i;
	sum=0;
	print ("%i,%i\n\0",fst, lst);
	for (i=1; i<=a->quof[fst]; i++) {
		if (a->quof[fst]%i==0) {
			for (j=1; j<=a->quof[lst]; j++) {
				if (a->quof[lst]%j==0) {
					sum=0;
					for (k=0; k<MAXS; k++) {
						sum += a->quof[k]*x_pow(((double)i / (double)j), k);
					}
					if (fabs(sum)<=0.0001) print("%i/%i is a zero\n\0",i,j); //Once poly_division is done, this can be upated to find factors  
				}
			}
		}
	}
	//aplly wikipedia's method to a simplified equation(reduces complexity)
	//TD
	return;
}

int main() {
	poly a, b, c;
	init_poly(&a); init_poly(&b); init_poly(&c); //inits the polys
	a.quof[4]=2; a.quof[3]=-11; a.quof[2]=-6; a.quof[1]=64; a.quof[0]=32; //set a to someting;
	printandfind(&a);
	init_poly(&a);
	a.quof[2]=1; a.quof[1]=-7; a.quof[0]=12;
	printandfind(&a);
	return 0;
}