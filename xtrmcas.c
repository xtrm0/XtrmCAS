#include "stdio.h"
#include "xnum.h"

int main() {
	num a1, a2, a3;
	num_init_d(&a1, 7);
	num_init(&a2);
	printf("\n");
	num_print(&a1);
	printf("\n");
	num_print(&a2);
	num_add(&a1,&a2,&a3);
	printf("\n");
	num_print(&a1);
	printf("\n");
	num_print(&a2);
	printf("\n");
	num_print(&a3);
	printf("\n");
	num_mult(&a1,&a3,&a2);
	num_print(&a1);
	printf("\n");
	num_print(&a2);
	printf("\n");
	num_print(&a3);
	printf("\n");
	num_sub(&a2,&a3,&a1);
	num_print(&a1);
	printf("\n");
	num_print(&a2);
	printf("\n");
	num_print(&a3);
	printf("\n");
	return 0;
}