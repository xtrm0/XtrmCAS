#include "xnum.h"

void num_init(num *c) {
  int i;
  c->signal = 1;
  c->right=0;
  for (i=0; i<MAX_COL; i++) 
    c->valz[i]=0;
}

void num_init_d(num *c, int a) {
  num_init(c);
  c->valz[0] = a % COL_SZ;
  if (a>=COL_SZ) {
    c->valz[1] = (a / COL_SZ) % COL_SZ;
    c->right = 1;
    if (a>=(lli)COL_SZ*(lli)COL_SZ) {
      c->valz[2] = a / ((lli)COL_SZ*(lli)COL_SZ);
    c->right = 2; //this is intended to be the maximum val. Anything that goes behond this is redundant, therefore we use no loops.
    }
  }
  c->signal = ((a>=0) ? 1 : -1);
}

void num_copy(num *a, num *c)  {
  int i;
  for (i=0; i<MAX_COL; i++) 
    c->valz[i] = a->valz[i];
  c->right = a->right;
  c->signal = a->signal;
}


int num_cmp(num *a, num *b) {
  int i;
  if (a->signal == b->signal) {
    if (a->signal == 1) {
      if (a->right > b->right) return 1;
      if (a->right < b->right) return -1;
      for (i=a->right; i>=0; i--) {
	if (a->valz[i] != b->valz[i]) return (a->valz[i] > b->valz[i] ? 1 : -1);
      }
      return 0;
    } else {
      if (a->right > b->right) return -1;
      if (a->right < b->right) return 1;
      for (i=a->right; i>=0; i--) {
	if (a->valz[i] != b->valz[i]) return (a->valz[i] < b->valz[i] ? 1 : -1);
      }
      return 0;
    }
  } else {
    if (a->signal == 1) {
      return 1;
    } else {
      return -1;
    }
  }
}


int num_cmp_abs(num *a, num *b) {
  int i;
  if (a->right > b->right) return 1;
  if (a->right < b->right) return -1;
  for (i=a->right; i>=0; i--) {
    if (a->valz[i] != b->valz[i]) return (a->valz[i] > b->valz[i] ? 1 : -1);
  }
  return 0;
}

void num_add(num *a, num *b, num *c) {
  lli trans=0;
  int i;
  int flag=0;
  num_init(c);
  if (a->signal * b->signal == 1) {
    c->right = max(a->right, b->right);
    for (i=0; i<=c->right; i++) {
      c->valz[i] = (a->valz[i] + b->valz[i] + trans)%COL_SZ;
      trans = (a->valz[i] + b->valz[i] + trans)/COL_SZ;
    }
    if (trans!=0) {
      c->right+=1;
      c->valz[c->right] = trans;
    }
    c->signal = a->signal;
  } else {
    if (num_cmp_abs(a,b) == -1) {
      flag = 1;
      num_print(a);
      printf("\n");
      num_print(b);
      printf("\n");
      num_swap(a,b);
      printf("flagged\n");
      num_print(a);
      printf("\n");
      num_print(b);
      printf("\n");
    }
    c->right = a->right;
    for (i=0; i<=c->right; i++) {
      if (a->valz[i] < (b->valz[i] + trans)) {
	c->valz[i] = (a->valz[i] + COL_SZ) - (b->valz[i] + trans);
	trans=1;
      } else {
	c->valz[i] = (a->valz[i]) - (b->valz[i] + trans);
	trans=0;
      }
    }
    
    c->signal = ((flag==1) ? -1 : 1);
    if (flag==1) num_swap(a,b);
  }
}

void num_sub(num *a, num *b, num *c) {
  //THAT WAS EASY
  b->signal*=-1;
  num_add(a,b,c);
  b->signal*=-1;
}

void num_mult(num *a, num *b, num *c) {
  //TODO: this is slow for n bigger than 200, if we make arbitraly bigintegers, we should change to karatsuba
  int i,j;
  lli trans=0;
  lli tmp;
  num_init(c);
  for (i=0; i<a->right; i++) {
    for (j=0; j<b->right; i++) {
      c->valz[i+j] += a->valz[i]*b->valz[j];
    }
  }
  for (i=0; i<MAX_COL; i++) {
    tmp = c->valz[i]+trans;
    c->valz[i] = (c->valz[i]+trans)%COL_SZ;
    trans = tmp/COL_SZ;
  }
  i = MAX_COL;
  while (c->valz[--i]==0);
  c->right = i;
  c->signal = ((c->right==0 && c->valz[0]==0) ? 1 : a->signal * b->signal);
}



void num_print(num *a) {
  //TODO connect this to console.c
  int i;
  if (a->signal == -1) printf("-#");
  printf("%d", (int)a->valz[a->right]);  //TODO make this pretier (remove int typecast)
  for (i=a->right-1; i>=0; i--) {
    printf(PADSTR, (int)a->valz[i]); //TODO make this pretier (remove int typecast)
  }
}



void num_swap(num *a, num *b) {
  lli tmp;
  int i;
  i = a->signal;
  a->signal = b->signal;
  b->signal = i;
  i = a->right;
  a->right = b->right;
  b->right = i;
  for (i=0; i<MAX_COL; i++) {
    tmp = a->valz[i];
    a->valz[i] = b->valz[i];
    b->valz[i] = tmp;
  }
}
