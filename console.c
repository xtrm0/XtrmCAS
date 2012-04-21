#include <fxlib.h>
#include <stdarg.h>
#include "MonochromeLib.h"
#include "console.h"

#define BUFFER_SIZE 1024

char inputBuffer[BUFFER_SIZE], *inputPtr;
int inputSize=0;
int cur;

static int SysCallCode[] = {0xD201422B,0x60F20000,0x80010070};
static int (*SysCall)( int R4, int R5, int R6, int R7, int FNo ) = (void*)&SysCallCode;

void Cursor_SetFlashMode(long flashmode)
{
	(*SysCall)(flashmode, 0, 0, 0, 0x13A);
}


void clear()
{
	inputSize = 0;
	cur = 0;
	ML_clear_vram();
}

void putchar(char c)
{
	if(c == '\n') {
		cur = 21 * (cur/21 + 1);
	} else {
		locate((cur%21)+1, (cur/21)+1);
		PrintC(&c);
		cur++;
	}
	if(cur >= 8*21) {
		ML_vertical_scroll(-8);
		cur -= 21;
		locate(1, 8);
		Print("                     ");
		locate(1, 8);
	}
	ML_display_vram();
}

void print(char* str, ...)
{
	va_list ap;
	va_start(ap, str);
	for( ; *str ; str++)
		if(*str == '%') {
			switch(*(++str)) {
				case '%': putchar('%'); break;
				case 'c': putchar(va_arg(ap, char)); break;
				case 'i': print_int(va_arg(ap, int)); break;
			}
		} else putchar(*str);
	va_end(ap);
}

void print_int(int n)
{
	int i;
	if(n < 0) putchar('-'), n = -n;
	for(i=1 ; n/i ; i*=10);
	for(i/=10 ; i ; i/=10) putchar((n/i)%10+'0');
}

char getchar()
{
	if(inputSize) {
		inputSize--;
		inputPtr++;
	} else {
		unsigned int key = 0;
		inputPtr = inputBuffer;
		locate((cur%21)+1, (cur/21)+1);
		Cursor_SetFlashMode(1);
		while(IsKeyDown(KEY_CTRL_EXE));
		while(key != KEY_CTRL_EXE) {
			GetKey(&key);
			if(key == KEY_CTRL_DEL && inputSize) {
				cur--;
				putchar(' ');
				cur--;
				locate((cur%21)+1, (cur/21)+1);
				inputSize--;
				inputPtr--;
			}
			if (key==KEY_CHAR_MULT && inputSize<BUFFER_SIZE-1) {
				putchar('*');
				*inputPtr = '*';
				inputPtr++;
				inputSize++;
			} else if (key==KEY_CHAR_DIV && inputSize<BUFFER_SIZE-1) {
				putchar('/');
				*inputPtr = '/';
				inputPtr++;
				inputSize++;
			} else if (key==KEY_CHAR_PLUS && inputSize<BUFFER_SIZE-1) {
				putchar('+');
				*inputPtr = '+';
				inputPtr++;
				inputSize++;
			} else if (key==KEY_CHAR_MINUS && inputSize<BUFFER_SIZE-1) {
				putchar('-');
				*inputPtr = '-';
				inputPtr++;
				inputSize++;
			} else if (key==KEY_CTRL_XTT && inputSize<BUFFER_SIZE-1) {
				putchar('x');
				*inputPtr = 'x';
				inputPtr++;
				inputSize++;
			} else if (key==KEY_CHAR_POW && inputSize<BUFFER_SIZE-1) {
				putchar('^');
				*inputPtr = '^';
				inputPtr++;
				inputSize++;
			} else if (key==KEY_CHAR_SQUARE && inputSize<BUFFER_SIZE-1) {
				putchar('^');
				*inputPtr = '^';
				inputPtr++;
				inputSize++;
				putchar('2');
				*inputPtr = '2';
				inputPtr++;
				inputSize++;
			} else if (key==KEY_CTRL_EXIT && inputSize<BUFFER_SIZE-1) {
				putchar('q');
				*inputPtr = 'q';
				inputPtr++;
				inputSize++;
				break;
			} else if(key < 256 && inputSize<BUFFER_SIZE-1) {
				putchar(key);
				*inputPtr = key;
				inputPtr++;
				inputSize++;
			}
		}
		putchar('\n');
		*inputPtr = '\n';
		inputPtr = inputBuffer;
		Cursor_SetFlashMode(0);
		while(IsKeyDown(KEY_CTRL_EXE));
	}
	return *inputPtr;
}
