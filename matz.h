#ifndef _MATZ
#define _MATZ
int x_gcd(int a,int b) {
    int c;
    if(a<b) {
        c = a;
        a = b;
        b = c;
    }
    while(1) {
        c = a%b;
  	    if(c==0)
            return b;
        a = b;
        b = c;
   }
}

int x_lcm(int a, int b) { 
    return ((a*b)/x_gcd(a,b));
}
#endif

