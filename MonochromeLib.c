/*************************************************************/
/** MonochromeLib - monochrome graphic library for fx-9860G **/
/** MonochromeLib is free software                          **/
/**                                                         **/
/** @author Pierre "PierrotLL" Le Gall                      **/
/** @contact legallpierre89@gmail.com                       **/
/**                                                         **/
/** @file MonochromeLib.c                                   **/
/** Code file of MonochromeLib                              **/
/**                                                         **/
/** @date 11-22-2011                                        **/
/*************************************************************/

#include "MonochromeLib.h"
#include <stdlib.h>


/******************************/
/** Dependencies management  **/
/******************************/

#ifdef ML_ALL
	#define ML_CLEAR_VRAM
	#define ML_CLEAR_SCREEN
	#define ML_DISPLAY_VRAM
	#define ML_SET_CONTRAST
	#define ML_GET_CONTRAST
	#define ML_PIXEL
	#define ML_POINT
	#define ML_PIXEL_TEST
	#define ML_LINE
	#define ML_HORIZONTAL_LINE
	#define ML_VERTICAL_LINE
	#define ML_RECTANGLE
	#define ML_POLYGON
	#define ML_FILLED_POLYGON
	#define ML_CIRCLE
	#define ML_FILLED_CIRCLE
	#define ML_ELLIPSE
	#define ML_ELLIPSE_IN_RECT
	#define ML_FILLED_ELLIPSE
	#define ML_FILLED_ELLIPSE_IN_RECT
	#define ML_HORIZONTAL_SCROLL
	#define ML_VERTICAL_SCROLL
	#define ML_BMP_OR
	#define ML_BMP_AND
	#define ML_BMP_XOR
	#define ML_BMP_OR_CL
	#define ML_BMP_AND_CL
	#define ML_BMP_XOR_CL
	#define ML_BMP_8_OR
	#define ML_BMP_8_AND
	#define ML_BMP_8_XOR
	#define ML_BMP_8_OR_CL
	#define ML_BMP_8_AND_CL
	#define ML_BMP_8_XOR_CL
	#define ML_BMP_16_OR
	#define ML_BMP_16_AND
	#define ML_BMP_16_XOR
	#define ML_BMP_16_OR_CL
	#define ML_BMP_16_AND_CL
	#define ML_BMP_16_XOR_CL
#endif

#ifdef ML_POLYGON
	#define ML_LINE
#endif

#ifdef ML_LINE
	#define ML_PIXEL
#endif

#ifdef ML_POINT
	#define ML_PIXEL
	#define ML_RECTANGLE
#endif

#ifdef ML_RECTANGLE
	#define ML_HORIZONTAL_LINE
#endif

#ifdef ML_FILLED_POLYGON
	#define ML_HORIZONTAL_LINE
#endif

#ifdef ML_CIRCLE
	#define ML_PIXEL
#endif

#ifdef ML_FILLED_CIRCLE
	#define ML_HORIZONTAL_LINE
#endif

#ifdef ML_ELLIPSE_IN_RECT
	#define ML_ELLIPSE
#endif

#ifdef ML_ELLIPSE
	#define ML_PIXEL
#endif

#ifdef ML_FILLED_ELLIPSE_IN_RECT
	#define ML_FILLED_ELLIPSE
#endif

#ifdef ML_FILLED_ELLIPSE
	#define ML_HORIZONTAL_LINE
#endif


/***************/
/** Functions **/
/***************/

#define sgn(x)	(x<0?-1:1)
#define rnd(x)	((int)(x+0.5))

//Thanks to Simon Lothar for this function
static int SysCallCode[] = {0xD201422B,0x60F20000,0x80010070};
static int (*SysCall)( int R4, int R5, int R6, int R7, int FNo ) = (void*)&SysCallCode;
char* ML_vram_adress()
{
	return (char*)((*SysCall)(0, 0, 0, 0, 309));
}

#ifdef ML_CLEAR_VRAM
void ML_clear_vram()
{
	int i, end, *pointer_long, vram;
	char *pointer_byte;
	vram = (int)ML_vram_adress();
	end = 4-vram&3;
	pointer_byte = (char*)vram;
	for(i=0 ; i<end ; i++) pointer_byte[i] = 0;
	pointer_long = (int*) (vram+end);
	for(i=0 ; i<255 ; i++) pointer_long[i] = 0;
	pointer_byte += 1020+end;
	end = vram&3;
	for(i=0 ; i<end ; i++) pointer_byte[i] = 0;
}
#endif

#ifdef ML_CLEAR_SCREEN
void ML_clear_screen()
{
	char *LCD_register_selector = (char*)0xB4000000, *LCD_data_register = (char*)0xB4010000;
	int i, j;
	for(i=0 ; i<64 ; i++)
	{
		*LCD_register_selector = 4;
		*LCD_data_register = i|192;
		*LCD_register_selector = 4;
		*LCD_data_register = 0;
		*LCD_register_selector = 7;
		for(j=0 ; j<16 ; j++) *LCD_data_register = 0;
	}
}
#endif

#ifdef ML_DISPLAY_VRAM
void ML_display_vram()
{
	char *LCD_register_selector = (char*)0xB4000000, *LCD_data_register = (char*)0xB4010000, *vram;
	int i, j;
	vram = ML_vram_adress();
	for(i=0 ; i<64 ; i++)
	{
		*LCD_register_selector = 4;
		*LCD_data_register = i|192;
		*LCD_register_selector = 4;
		*LCD_data_register = 0;
		*LCD_register_selector = 7;
		for(j=0 ; j<16 ; j++) *LCD_data_register = *vram++;
	}
}
#endif

#ifdef ML_SET_CONTRAST
void ML_set_contrast(unsigned char contrast)
{
	char *LCD_register_selector = (char*)0xB4000000, *LCD_data_register = (char*)0xB4010000;
	*LCD_register_selector = 6;
	*LCD_data_register = contrast;
}
#endif

#ifdef ML_GET_CONTRAST
unsigned char ML_get_contrast()
{
	char *LCD_register_selector = (char*)0xB4000000, *LCD_data_register = (char*)0xB4010000;
	*LCD_register_selector = 6;
	return *LCD_data_register;
}
#endif

#ifdef ML_PIXEL
void ML_pixel(int x, int y, ML_Color color)
{
	char* vram = ML_vram_adress();
	if(x&~127 || y&~63) return;
	switch(color)
	{
		case ML_BLACK:
			vram[(y<<4)+(x>>3)] |= 128>>(x&7);
			break;
		case ML_WHITE:
			vram[(y<<4)+(x>>3)] &= ~(128>>(x&7));
			break;
		case ML_XOR:
			vram[(y<<4)+(x>>3)] ^= 128>>(x&7);
			break;
		case ML_CHECKER:
			if(y&1^x&1) vram[(y<<4)+(x>>3)] &= ~(128>>(x&7));
			else vram[(y<<4)+(x>>3)] |= 128>>(x&7);
			break;
	}
}
#endif

#ifdef ML_POINT
void ML_point(int x, int y, int width, ML_Color color)
{
	if(width < 1) return;
	if(width == 1) ML_pixel(x, y, color);
	else
	{
		int padding, pair;
		padding = width>>1;
		pair = !(width&1);
		ML_rectangle(x-padding+pair, y-padding+pair, x+padding, y+padding, 0, 0, color);
	}
}
#endif

#ifdef ML_PIXEL_TEST
ML_Color ML_pixel_test(int x, int y)
{
	char *vram, byte;
	if(x&~127 || y&~63) return ML_TRANSPARENT;
	vram = ML_vram_adress();
	byte = 1<<(7-(x&7));
	return (vram[(y<<4)+(x>>3)] & byte ? ML_BLACK : ML_WHITE);
	
}
#endif

#ifdef ML_LINE
void ML_line(int x1, int y1, int x2, int y2, ML_Color color)
{
	int i, x, y, dx, dy, sx, sy, cumul;
	x = x1;
	y = y1;
	dx = x2 - x1;
	dy = y2 - y1;
	sx = sgn(dx);
	sy = sgn(dy);
	dx = abs(dx);
	dy = abs(dy);
	ML_pixel(x, y, color);
	if(dx > dy)
	{
		cumul = dx / 2;
		for(i=1 ; i<dx ; i++)
		{
			x += sx;
			cumul += dy;
			if(cumul > dx)
			{
				cumul -= dx;
				y += sy;
			}
			ML_pixel(x, y, color);
		}
	}
	else
	{
		cumul = dy / 2;
		for(i=1 ; i<dy ; i++)
		{
			y += sy;
			cumul += dx;
			if(cumul > dy)
			{
				cumul -= dy;
				x += sx;
			}
			ML_pixel(x, y, color);
		}
	}
}
#endif

#ifdef ML_HORIZONTAL_LINE
void ML_horizontal_line(int y, int x1, int x2, ML_Color color)
{
    int i;
    char checker;
    char* vram = ML_vram_adress();
    if(y&~63 || (x1<0 && x2<0) || (x1>127 && x2>127)) return;
    if(x1 > x2)
    {
    	i = x1;
    	x1 = x2;
    	x2 = i;
    }
    if(x1 < 0) x1 = 0;
    if(x2 > 127) x2 = 127;
    switch(color)
    {
    	case ML_BLACK:
			if(x1>>3 != x2>>3)
			{
				vram[(y<<4)+(x1>>3)] |= 255 >> (x1&7);
				vram[(y<<4)+(x2>>3)] |= 255 << 7-(x2&7);
				for(i=(x1>>3)+1 ; i<x2>>3 ; i++)
					vram[(y<<4) + i] = 255;
			}
			else vram[(y<<4)+(x1>>3)] |= (255>>(x1%8 + 7-x2%8))<<(7-(x2&7));
			break;
		case ML_WHITE:
			if(x1>>3 != x2>>3)
			{
				vram[(y<<4)+(x1>>3)] &= 255 << 8-(x1&7);
				vram[(y<<4)+(x2>>3)] &= 255 >> 1+(x2&7);
				for(i=(x1>>3)+1 ; i<x2>>3 ; i++)
					vram[(y<<4) + i] = 0;
			}
			else vram[(y<<4)+(x1>>3)] &= (255<<8-(x1&7)) | (255>>1+(x2&7));
			break;
		case ML_XOR:
			if(x1>>3 != x2>>3)
			{
				vram[(y<<4)+(x1>>3)] ^= 255 >> (x1&7);
				vram[(y<<4)+(x2>>3)] ^= 255 << 7-(x2&7);
				for(i=(x1>>3)+1 ; i<(x2>>3) ; i++)
					vram[(y<<4) + i] ^= 255;
			}
			else vram[(y<<4)+(x1>>3)] ^= (255>>((x1&7) + 7-(x2&7)))<<(7-(x2&7));
			break;
		case ML_CHECKER:
			checker = (y&1 ? 85 : 170);
			if(x1>>3 != x2>>3)
			{
				vram[(y<<4)+(x1>>3)] &= 255 << 8-(x1&7);
				vram[(y<<4)+(x2>>3)] &= 255 >> 1+(x2&7);
				vram[(y<<4)+(x1>>3)] |= checker & 255>>(x1&7);
				vram[(y<<4)+(x2>>3)] |= checker & 255<<7-(x2&7);
				for(i=(x1>>3)+1 ; i<x2>>3 ; i++)
					vram[(y<<4) + i] = checker;
			}
			else
			{
				vram[(y<<4)+(x1>>3)] &= (255<<8-(x1&7)) | (255>>1+(x2&7));
				vram[(y<<4)+(x1>>3)] |= checker & (255>>(x1%8 + 7-x2%8))<<(7-(x2&7));
			}
			break;
    }
}

#endif

#ifdef ML_VERTICAL_LINE
void ML_vertical_line(int x, int y1, int y2, ML_Color color)
{
    int i, j;
    char checker, byte, *vram = ML_vram_adress();
	if(x&~127 || (y1<0 && y2<0) || (y1>63 && y2>63)) return;
	if(y1 > y2)
	{
		int tmp = y1;
		y1 = y2;
		y2 = tmp;
	}
	if(y1 < 0) y1 = 0;
	if(y2 > 63) y2 = 63;

	i = (y1<<4)+(x>>3);
	j = (y2<<4)+(x>>3);
	switch(color)
	{
		case ML_BLACK:
			byte = 128>>(x&7);
			for( ; i<=j ; i+=16)
				vram[i] |= byte;
			break;
		case ML_WHITE:
			byte = ~(128>>(x&7));
			for( ; i<=j ; i+=16)
				vram[i] &= byte;
			break;
		case ML_XOR:
			byte = 128>>(x&7);
			for( ; i<=j ; i+=16)
				vram[i] ^= byte;
			break;
		case ML_CHECKER:
			byte = 128>>(x&7);
			checker = y1&1^x&1;
			for( ; i<=j ; i+=16)
			{
				if(checker) vram[i] &= ~byte;
				else vram[i] |= byte;
				checker = !checker;
			}
			break;
	}
}
#endif

#ifdef ML_RECTANGLE
void ML_rectangle(int x1, int y1, int x2, int y2, int border_width, ML_Color border_color, ML_Color fill_color)
{
	int i;
	if(x1 > x2)
	{
		i = x1;
		x1 = x2;
		x2 = i;
	}
	if(y1 > y2)
	{
		i = y1;
		y1 = y2;
		y2 = i;
	}
	if(border_width > (x2-x1)/2+1) border_width = (x2-x1)/2+1;
	if(border_width > (y2-y1)/2+1) border_width = (y2-y1)/2+1;
	if(border_color != ML_TRANSPARENT && border_width > 0)
	{
		for(i=0 ; i<border_width ; i++)
		{
			ML_horizontal_line(y1+i, x1, x2, border_color);
			ML_horizontal_line(y2-i, x1, x2, border_color);
		}
		for(i=y1+border_width ; i<=y2-border_width ; i++)
		{
			ML_horizontal_line(i, x1, x1+border_width-1, border_color);
			ML_horizontal_line(i, x2-border_width+1, x2, border_color);
		}
	}
	if(fill_color != ML_TRANSPARENT)
	{
		for(i=y1+border_width ; i<=y2-border_width ; i++)
			ML_horizontal_line(i, x1+border_width, x2-border_width, fill_color);
	}
}
#endif

#ifdef ML_POLYGON
void ML_polygon(const int *x, const int *y, int nb_vertices, ML_Color color)
{
	int i;
	if(nb_vertices < 1) return;
	for(i=0 ; i<nb_vertices-1 ; i++)
		ML_line(x[i], y[i], x[i+1], y[i+1], color);
	ML_line(x[i], y[i], x[0], y[0], color);
}
#endif

#ifdef ML_FILLED_POLYGON
static int ML_filled_polygon_quicksord_partition(int *t, int p, int r)
{
	int i, j, x, tmp;
	j = p - 1;
	x = t[r];
	for(i=p ; i<r ; i++)
	{
		if(x > t[i])
		{
			j++;
			tmp = t[j];
			t[j] = t[i];
			t[i] = tmp;
		}
	}
	t[r] = t[j+1];
	t[j+1] = x;
	return j + 1;
}

static void ML_filled_polygon_quicksord(int* t, int p, int r)
{
	int q;
	if(p < r)
	{
		q = ML_filled_polygon_quicksord_partition(t, p, r);
		ML_filled_polygon_quicksord(t, p, q-1);
		ML_filled_polygon_quicksord(t, q+1, r);
	}
}


void ML_filled_polygon(const int *x, const int *y, int nb_vertices, ML_Color color)
{
	int i, j, dx, dy, ymin, ymax;
	int *cut_in_line, nb_cut;
	if(nb_vertices < 3) return;
	cut_in_line = malloc(nb_vertices*sizeof(int));
	if(!cut_in_line) return;
	ymin = ymax = y[0];
	for(i=1 ; i<nb_vertices ; i++)
	{
		if(y[i] < ymin) ymin = y[i];
		if(y[i] > ymax) ymax = y[i];
	}
	for(i=ymin ; i<=ymax ; i++)
	{
		nb_cut = 0;
		for(j=0 ; j<nb_vertices ; j++)
		{
			if((y[j]<=i && y[(j+1)%nb_vertices]>=i) || (y[j]>=i && y[(j+1)%nb_vertices]<=i))
			{
				dy = abs(y[j]-y[(j+1)%nb_vertices]);
				if(dy)
				{
					dx = x[(j+1)%nb_vertices]-x[j];
					cut_in_line[nb_cut] = x[j] + rnd(abs(i-y[j]+sgn(i-y[j])/2)*dx/dy);
					nb_cut++;
				}
			}
		}
		ML_filled_polygon_quicksord(cut_in_line, 0, nb_cut-1);
		j = 0;
		while(j<nb_cut-2 && cut_in_line[j]==cut_in_line[j+1]) j++;
		while(j < nb_cut)
		{
			if(j == nb_cut-1) ML_horizontal_line(i, cut_in_line[j-1]+1, cut_in_line[j], color);
			else
			{
				dx = 1;
				while(j+dx<nb_cut-1 && cut_in_line[j+dx]==cut_in_line[j+dx+1]) dx++;
				ML_horizontal_line(i, cut_in_line[j], cut_in_line[j+dx], color);
				j += dx;
			}
			j++;
		}
	}
	free(cut_in_line);
}
#endif

#ifdef ML_CIRCLE
void ML_circle(int x, int y, int radius, ML_Color color)
{
	int plot_x, plot_y, d;

	if(radius < 0) return;
	plot_x = 0;
	plot_y = radius;
	d = 1 - radius;

	ML_pixel(x, y+plot_y, color);
	if(radius)
	{
		ML_pixel(x, y-plot_y, color);
		ML_pixel(x+plot_y, y, color);
		ML_pixel(x-plot_y, y, color);
	}
	while(plot_y > plot_x)
	{
		if(d < 0)
			d += 2*plot_x+3;
		else
		{
			d += 2*(plot_x-plot_y)+5;
			plot_y--;
		}
		plot_x++;
		if(plot_y >= plot_x)
		{
			ML_pixel(x+plot_x, y+plot_y, color);
			ML_pixel(x-plot_x, y+plot_y, color);
			ML_pixel(x+plot_x, y-plot_y, color);
			ML_pixel(x-plot_x, y-plot_y, color);
		}
		if(plot_y > plot_x)
		{
			ML_pixel(x+plot_y, y+plot_x, color);
			ML_pixel(x-plot_y, y+plot_x, color);
			ML_pixel(x+plot_y, y-plot_x, color);
			ML_pixel(x-plot_y, y-plot_x, color);
		}
	}
}
#endif

#ifdef ML_FILLED_CIRCLE
void ML_filled_circle(int x, int y, int radius, ML_Color color)
{
	int plot_x, plot_y, d;

	if(radius < 0) return;
	plot_x = 0;
	plot_y = radius;
	d = 1 - radius;

	ML_horizontal_line(y, x-plot_y, x+plot_y, color);
	while(plot_y > plot_x)
	{
		if(d < 0)
			d += 2*plot_x+3;
		else {
			d += 2*(plot_x-plot_y)+5;
			plot_y--;
			ML_horizontal_line(y+plot_y+1, x-plot_x, x+plot_x, color);
			ML_horizontal_line(y-plot_y-1, x-plot_x, x+plot_x, color);
		}
		plot_x++;
		if(plot_y >= plot_x)
		{
			ML_horizontal_line(y+plot_x, x-plot_y, x+plot_y, color);
			ML_horizontal_line(y-plot_x, x-plot_y, x+plot_y, color);
		}
	}
}
#endif

#ifdef ML_ELLIPSE
void ML_ellipse(int x, int y, int radius1, int radius2, ML_Color color)
{
	int plot_x, plot_y;
	float d1, d2;
	if(radius1 < 1 || radius2 < 1) return;
	plot_x = 0;
	plot_y = radius2;
	d1 = radius2*radius2 - radius1*radius1*radius2 + radius1*radius1/4;
	ML_pixel(x, y+plot_y, color);
	ML_pixel(x, y-plot_y, color);
	while(radius1*radius1*(plot_y-.5) > radius2*radius2*(plot_x+1))
	{
		if(d1 < 0)
		{
			d1 += radius2*radius2*(2*plot_x+3);
			plot_x++;
		} else {
			d1 += radius2*radius2*(2*plot_x+3) + radius1*radius1*(-2*plot_y+2);
			plot_x++;
			plot_y--;
		}
		ML_pixel(x+plot_x, y+plot_y, color);
		ML_pixel(x-plot_x, y+plot_y, color);
		ML_pixel(x+plot_x, y-plot_y, color);
		ML_pixel(x-plot_x, y-plot_y, color);
	}
	d2 = radius2*radius2*(plot_x+.5)*(plot_x+.5) + radius1*radius1*(plot_y-1)*(plot_y-1) - radius1*radius1*radius2*radius2;
	while(plot_y > 0)
	{
		if(d2 < 0)
		{
			d2 += radius2*radius2*(2*plot_x+2) + radius1*radius1*(-2*plot_y+3);
			plot_y--;
			plot_x++;
		} else {
			d2 += radius1*radius1*(-2*plot_y+3);
			plot_y--;
		}
		ML_pixel(x+plot_x, y+plot_y, color);
		ML_pixel(x-plot_x, y+plot_y, color);
		if(plot_y > 0)
		{
			ML_pixel(x+plot_x, y-plot_y, color);
			ML_pixel(x-plot_x, y-plot_y, color);
		}
	}
}
#endif

#ifdef ML_ELLIPSE_IN_RECT
void ML_ellipse_in_rect(int x1, int y1, int x2, int y2, ML_Color color)
{
	int radius1, radius2;
	if(x1 > x2)
	{
		int tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
	if(y1 > y2)
	{
		int tmp = y1;
		y1 = y2;
		y2 = tmp;
	}
	radius1 = (x2-x1)/2;
	radius2 = (y2-y1)/2;
	ML_ellipse(x1+radius1, y1+radius2, radius1, radius2, color);
}
#endif

#ifdef ML_FILLED_ELLIPSE
void ML_filled_ellipse(int x, int y, int radius1, int radius2, ML_Color color)
{
	int plot_x, plot_y;
	float d1, d2;
	if(radius1 < 1 || radius2 < 1) return;
	plot_x = 0;
	plot_y = radius2;
	d1 = radius2*radius2 - radius1*radius1*radius2 + radius1*radius1/4;
	while(radius1*radius1*(plot_y-.5) > radius2*radius2*(plot_x+1))
	{
		if(d1 < 0)
		{
			d1 += radius2*radius2*(2*plot_x+3);
			plot_x++;
		} else {
			d1 += radius2*radius2*(2*plot_x+3) + radius1*radius1*(-2*plot_y+2);
			ML_horizontal_line(y+plot_y, x-plot_x, x+plot_x, color);
			ML_horizontal_line(y-plot_y, x-plot_x, x+plot_x, color);
			plot_x++;
			plot_y--;
		}
	}
	ML_horizontal_line(y+plot_y, x-plot_x, x+plot_x, color);
	ML_horizontal_line(y-plot_y, x-plot_x, x+plot_x, color);
	d2 = radius2*radius2*(plot_x+.5)*(plot_x+.5) + radius1*radius1*(plot_y-1)*(plot_y-1) - radius1*radius1*radius2*radius2;
	while(plot_y > 0)
	{
		if(d2 < 0)
		{
			d2 += radius2*radius2*(2*plot_x+2) + radius1*radius1*(-2*plot_y+3);
			plot_y--;
			plot_x++;
		} else {
			d2 += radius1*radius1*(-2*plot_y+3);
			plot_y--;
		}
		ML_horizontal_line(y+plot_y, x-plot_x, x+plot_x, color);
		if(plot_y > 0)
			ML_horizontal_line(y-plot_y, x-plot_x, x+plot_x, color);
	}
}
#endif

#ifdef ML_FILLED_ELLIPSE_IN_RECT
void ML_filled_ellipse_in_rect(int x1, int y1, int x2, int y2, ML_Color color)
{
	int radius1, radius2;
	if(x1 > x2)
	{
		int tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
	if(y1 > y2)
	{
		int tmp = y1;
		y1 = y2;
		y2 = tmp;
	}
	radius1 = (x2-x1)/2;
	radius2 = (y2-y1)/2;
	ML_filled_ellipse(x1+radius1, y1+radius2, radius1, radius2, color);
}
#endif

#ifdef ML_HORIZONTAL_SCROLL
void ML_horizontal_scroll(int scroll)
{
	int i, j;
	char line[16], shift, *vram;
	unsigned char next;
	unsigned short word;
	vram = ML_vram_adress();
	scroll %= 128;
	shift = 8-(scroll&7);
	for(i=0 ; i<64 ; i++)
	{
		for(j=0 ; j<16 ; j++) line[j] = vram[(i<<4)+((j-(scroll>>3)+15)&15)];
		next = line[15];
		vram[(i<<4)+15] = 0;
		for(j=15 ; j>0 ; j--)
		{
			word = next << shift;
			next = line[j-1];
			vram[(i<<4)+j] |= *((char*)&word+1);
			vram[(i<<4)+j-1] = *((char*)&word);
		}
		word = next << shift;
		vram[(i<<4)] |= *((char*)&word+1);
		vram[(i<<4)+15] |= *((char*)&word);
	}
}
#endif

#ifdef ML_VERTICAL_SCROLL
void ML_vertical_scroll(int scroll)
{
	int i, j;
	char column[64], *vram = ML_vram_adress();
	scroll %= 64;
	for(i=0 ; i<16 ; i++)
	{
		for(j=0 ; j<64 ; j++) column[j] = vram[(j<<4)+i];
		for(j=0 ; j<64 ; j++) vram[(j<<4)+i] = column[(j-scroll+64)&63];
	}
}
#endif

#ifdef ML_BMP_OR
void ML_bmp_or(const unsigned char *bmp, int x, int y, int width, int height)
{
	unsigned short line;
	char shift, *screen, *p=(char*)&line;
	int i, j, begin=0, end=height, real_width=(width-1>>3<<3)+8;
	if(!bmp || x<0 || x>128-width || y<1-height || y>63 || width<1 || height<1) return;
	if(y < 0) begin = -y;
	if(y+height > 64) end = 64-y;
	shift = 8-(x&7);
	screen = ML_vram_adress()+(y+begin<<4)+(x>>3);
	for(i=begin ; i<end ; i++)
	{
		for(j=0 ; j<width-1>>3 ; j++)
		{
			line = bmp[i*(real_width>>3)+j]<<shift;
			screen[j] |= *p;
			if(shift!=8) screen[j+1] |= *(p+1);
		}
		line = (bmp[i*(real_width>>3)+j] & -1<<(real_width-width))<<shift;
		screen[j] |= *p;
		if(shift!=8 && x+real_width<129) screen[j+1] |= *(p+1);
		screen += 16;
	}
}
#endif

#ifdef ML_BMP_AND
void ML_bmp_and(const unsigned char *bmp, int x, int y, int width, int height)
{
	unsigned short line;
	char shift, *screen, *p=(char*)&line;
	int i, j, begin=0, end=height, real_width=(width-1>>3<<3)+8;
	if(!bmp || x<0 || x>128-width || y<1-height || y>63 || width<1 || height<1) return;
	if(y < 0) begin = -y;
	if(y+height > 64) end = 64-y;
	shift = 8-(x&7);
	screen = ML_vram_adress()+(y+begin<<4)+(x>>3);
	for(i=begin ; i<end ; i++)
	{
		for(j=0 ; j<width-1>>3 ; j++)
		{
			line = ~((unsigned char)~bmp[i*(real_width>>3)+j]<<shift);
			screen[j] &= *p;
			if(shift!=8) screen[j+1] &= *(p+1);
		}
		line = ~((unsigned char)~(bmp[i*(real_width>>3)+j] | (unsigned char)-1>>8-(width&7))<<shift);
		screen[j] &= *p;
		if(shift!=8 && x+real_width<129) screen[j+1] &= *(p+1);
		screen += 16;
	}
}
#endif

#ifdef ML_BMP_XOR
void ML_bmp_xor(const unsigned char *bmp, int x, int y, int width, int height)
{
	unsigned short line;
	char shift, *screen, *p=(char*)&line;
	int i, j, begin=0, end=height, real_width=(width-1>>3<<3)+8;
	if(!bmp || x<0 || x>128-width || y<1-height || y>63 || width<1 || height<1) return;
	if(y < 0) begin = -y;
	if(y+height > 64) end = 64-y;
	shift = 8-(x&7);
	screen = ML_vram_adress()+(y+begin<<4)+(x>>3);
	for(i=begin ; i<end ; i++)
	{
		for(j=0 ; j<width-1>>3 ; j++)
		{
			line = bmp[i*(real_width>>3)+j]<<shift;
			screen[j] ^= *p;
			if(shift!=8) screen[j+1] ^= *(p+1);
		}
		line = (bmp[i*(real_width>>3)+j] & -1<<(real_width-width))<<shift;
		screen[j] ^= *p;
		if(shift!=8 && x+real_width<129) screen[j+1] ^= *(p+1);
		screen += 16;
	}
}
#endif

#ifdef ML_BMP_OR_CL
void ML_bmp_or_cl(const unsigned char *bmp, int x, int y, int width, int height)
{
	unsigned short line;
	char shift, *screen, *p;
	int i, j, real_width, begin_x, end_x, begin_y, end_y;
	char bool1=1, bool2=1, bool3;
	if(!bmp || x<1-width || x>127 || y<1-height || y>63 || height<1 || width<1) return;
	p = (char*)&line;
	real_width = (width-1>>3<<3)+8;
	if(y < 0) begin_y = -y;
	else begin_y = 0;
	if(y+height > 64) end_y = 64-y;
	else end_y = height;
	shift = 8-(x&7);
	if(x<0)
	{
		begin_x = -x>>3;
		if(shift != 8) bool1 = 0;
	} else begin_x = 0;
	if(x+real_width > 128) end_x = 15-(x>>3), bool2 = 0;
	else end_x = real_width-1>>3;
	bool3 = (end_x == real_width-1>>3);
	screen = ML_vram_adress()+(y+begin_y<<4)+(x>>3);

	for(i=begin_y ; i<end_y ; i++)
	{
		if(begin_x < end_x)
		{
			line = bmp[i*(real_width>>3)+begin_x] << shift;
			if(bool1) screen[begin_x] |= *p;
			if(shift!=8) screen[begin_x+1] |= *(p+1);
			for(j=begin_x+1 ; j<end_x ; j++)
			{
				line = bmp[i*(real_width>>3)+j] << shift;
				screen[j] |= *p;
				if(shift!=8) screen[j+1] |= *(p+1);
			}
		}
		line = bmp[i*(real_width>>3)+end_x];
		if(bool3) line &= -1<<real_width-width;
		line <<= shift;
		if(begin_x < end_x || bool1) screen[end_x] |= *p;
		if(bool2) screen[end_x+1] |= *(p+1);
		screen += 16;
	}
}
#endif

#ifdef ML_BMP_AND_CL
void ML_bmp_and_cl(const unsigned char *bmp, int x, int y, int width, int height)
{
	unsigned short line;
	char shift, *screen, *p;
	int i, j, real_width, begin_x, end_x, begin_y, end_y;
	char bool1=1, bool2=1, bool3;
	if(!bmp || x<1-width || x>127 || y<1-height || y>63 || height<1 || width<1) return;
	p = (char*)&line;
	real_width = (width-1>>3<<3)+8;
	if(y < 0) begin_y = -y;
	else begin_y = 0;
	if(y+height > 64) end_y = 64-y;
	else end_y = height;
	shift = 8-(x&7);
	if(x<0)
	{
		begin_x = -x>>3;
		if(shift != 8) bool1 = 0;
	} else begin_x = 0;
	if(x+real_width > 128) end_x = 15-(x>>3), bool2 = 0;
	else end_x = real_width-1>>3;
	bool3 = (end_x == real_width-1>>3);
	screen = ML_vram_adress()+(y+begin_y<<4)+(x>>3);

	for(i=begin_y ; i<end_y ; i++)
	{
		if(begin_x < end_x)

		{
			line = ~((unsigned char)~bmp[i*(real_width>>3)+begin_x]<<shift);
			if(bool1) screen[begin_x] &= *p;
			if(shift!=8) screen[begin_x+1] &= *(p+1);
			for(j=begin_x+1 ; j<end_x ; j++)
			{
				line = ~((unsigned char)~bmp[i*(real_width>>3)+j]<<shift);
				screen[j] &= *p;
				if(shift!=8) screen[j+1] &= *(p+1);
			}
		}
		line = (unsigned char)~bmp[i*(real_width>>3)+end_x];
		if(bool3) line &= -1<<real_width-width;
		line = ~(line << shift);
		if(begin_x < end_x || bool1) screen[end_x] &= *p;
		if(bool2) screen[end_x+1] &= *(p+1);
		screen += 16;
	}
}
#endif

#ifdef ML_BMP_XOR_CL
void ML_bmp_xor_cl(const unsigned char *bmp, int x, int y, int width, int height)
{
	unsigned short line;
	char shift, *screen, *p;
	int i, j, real_width, begin_x, end_x, begin_y, end_y;
	char bool1=1, bool2=1, bool3;
	if(!bmp || x<1-width || x>127 || y<1-height || y>63 || height<1 || width<1) return;
	p = (char*)&line;
	real_width = (width-1>>3<<3)+8;
	if(y < 0) begin_y = -y;
	else begin_y = 0;
	if(y+height > 64) end_y = 64-y;
	else end_y = height;
	shift = 8-(x&7);
	if(x<0)
	{
		begin_x = -x>>3;
		if(shift != 8) bool1 = 0;
	} else begin_x = 0;
	if(x+real_width > 128) end_x = 15-(x>>3), bool2 = 0;
	else end_x = real_width-1>>3;
	bool3 = (end_x == real_width-1>>3);
	screen = ML_vram_adress()+(y+begin_y<<4)+(x>>3);

	for(i=begin_y ; i<end_y ; i++)
	{
		if(begin_x < end_x)
		{
			line = bmp[i*(real_width>>3)+begin_x] << shift;
			if(bool1) screen[begin_x] ^= *p;
			if(shift!=8) screen[begin_x+1] ^= *(p+1);
			for(j=begin_x+1 ; j<end_x ; j++)
			{
				line = bmp[i*(real_width>>3)+j] << shift;
				screen[j] ^= *p;
				if(shift!=8) screen[j+1] ^= *(p+1);
			}
		}
		line = bmp[i*(real_width>>3)+end_x];
		if(bool3) line &= -1<<real_width-width;
		line <<= shift;
		if(begin_x < end_x || bool1) screen[end_x] ^= *p;
		if(bool2) screen[end_x+1] ^= *(p+1);
		screen += 16;
	}
}

#endif

#ifdef ML_BMP_8_OR
void ML_bmp_8_or(const unsigned char *bmp, int x, int y)
{
	unsigned short line;
	char i, shift, begin=0, end=8, *screen, *p=(char*)&line;
	if(!bmp || x<0 || x>120 || y<-7 || y>63) return;
	if(y < 0) begin = -y;
	if(y > 56) end = 64-y;
	shift = 8-(x&7);
	screen = ML_vram_adress()+(y+begin<<4)+(x>>3);
	for(i=begin ; i<end ; i++)
	{
		line = bmp[i]<<shift;
		screen[0] |= *p;
		if(shift!=8) screen[1] |= *(p+1);
		screen += 16;
	}
}
#endif

#ifdef ML_BMP_8_AND
void ML_bmp_8_and(const unsigned char *bmp, int x, int y)
{
	unsigned short line;
	char i, shift, begin=0, end=8, *screen, *p=(char*)&line;
	if(!bmp || x<0 || x>120 || y<-7 || y>63) return;
	if(y < 0) begin = -y;
	if(y > 56) end = 64-y;
	shift = 8-(x&7);
	screen = ML_vram_adress()+(y+begin<<4)+(x>>3);
	for(i=begin ; i<end ; i++)
	{
		line = ~((unsigned char)~bmp[i]<<shift);
		screen[0] &= *p;
		if(shift!=8) screen[1] &= *(p+1);
		screen += 16;
	}
}
#endif

#ifdef ML_BMP_8_XOR
void ML_bmp_8_xor(const unsigned char *bmp, int x, int y)
{
	unsigned short line;
	char i, shift, begin=0, end=8, *screen, *p=(char*)&line;
	if(!bmp || x<0 || x>120 || y<-7 || y>63) return;
	if(y < 0) begin = -y;
	if(y > 56) end = 64-y;
	shift = 8-(x&7);
	screen = ML_vram_adress()+(y+begin<<4)+(x>>3);
	for(i=begin ; i<end ; i++)
	{
		line = bmp[i]<<shift;
		screen[0] ^= *p;
		if(shift<8) screen[1] ^= *(p+1);
		screen += 16;
	}
}
#endif

#ifdef ML_BMP_8_OR_CL
void ML_bmp_8_or_cl(const unsigned char *bmp, int x, int y)
{
	unsigned short line;
	char i, shift, begin=0, end=8, bool1=1, bool2=1, *screen, *p=(char*)&line;
	if(!bmp || x<-7 || x>127 || y<-7 || y>63) return;
	if(y < 0) begin = -y;
	if(y > 56) end = 64-y;
	shift = 8-(x&7);
	if(x < 0) bool1 = 0;
	if(x>120 || shift==8) bool2 = 0;
	screen = ML_vram_adress()+(y+begin<<4)+(x>>3);
	for(i=begin ; i<end ; i++)
	{
		line = bmp[i]<<shift;
		if(bool1) screen[0] |= *p;
		if(bool2) screen[1] |= *(p+1);
		screen += 16;
	}
}
#endif

#ifdef ML_BMP_8_AND_CL
void ML_bmp_8_and_cl(const unsigned char *bmp, int x, int y)
{
	unsigned short line;
	char i, shift, begin=0, end=8, bool1=1, bool2=1, *screen, *p=(char*)&line;
	if(!bmp || x<-7 || x>127 || y<-7 || y>63) return;
	if(y < 0) begin = -y;
	if(y > 56) end = 64-y;
	shift = 8-(x&7);
	if(x < 0) bool1 = 0;
	if(x>120 || shift==8) bool2 = 0;
	screen = ML_vram_adress()+(y+begin<<4)+(x>>3);
	for(i=begin ; i<end ; i++)
	{
		line = ~((unsigned char)~bmp[i]<<shift);
		if(bool1) screen[0] &= *p;
		if(bool2) screen[1] &= *(p+1);
		screen += 16;
	}
}
#endif

#ifdef ML_BMP_8_XOR_CL
void ML_bmp_8_xor_cl(const unsigned char *bmp, int x, int y)
{
	unsigned short line;
	char i, shift, begin=0, end=8, bool1=1, bool2=1, *screen, *p=(char*)&line;
	if(!bmp || x<-7 || x>127 || y<-7 || y>63) return;
	if(y < 0) begin = -y;
	if(y > 56) end = 64-y;
	shift = 8-(x&7);
	if(x < 0) bool1 = 0;
	if(x>120 || shift==8) bool2 = 0;
	screen = ML_vram_adress()+(y+begin<<4)+(x>>3);
	for(i=begin ; i<end ; i++)
	{
		line = bmp[i]<<shift;
		if(bool1) screen[0] ^= *p;
		if(bool2) screen[1] ^= *(p+1);
		screen += 16;
	}
}
#endif

#ifdef ML_BMP_16_OR
void ML_bmp_16_or(const unsigned short *bmp, int x, int y)
{
	unsigned long line;
	char i, shift, begin=0, end=16, *screen, *p=(char*)&line+1;
	if(!bmp || x<0 || x>112 || y<-15 || y>63) return;
	if(y < 0) begin = -y;
	if(y > 48) end = 64-y;
	shift = 8-(x&7);
	screen = ML_vram_adress()+(y+begin<<4)+(x>>3);
	for(i=begin ; i<end ; i++)
	{
		line = bmp[i]<<shift;
		screen[0] |= *p;
		screen[1] |= *(p+1);
		if(shift!=8) screen[2] |= *(p+2);
		screen += 16;
	}
}
#endif

#ifdef ML_BMP_16_AND
void ML_bmp_16_and(const unsigned short *bmp, int x, int y)
{
	unsigned long line;
	char i, shift, begin=0, end=16, *screen, *p=(char*)&line+1;
	if(!bmp || x<0 || x>112 || y<-15 || y>63) return;
	if(y < 0) begin = -y;
	if(y > 48) end = 64-y;
	shift = 8-(x&7);
	screen = ML_vram_adress()+(y+begin<<4)+(x>>3);
	for(i=begin ; i<end ; i++)
	{
		line = ~((unsigned short)~bmp[i]<<shift);
		screen[0] &= *p;
		screen[1] &= *(p+1);
		if(shift!=8) screen[2] &= *(p+2);
		screen += 16;
	}
}
#endif

#ifdef ML_BMP_16_XOR
void ML_bmp_16_xor(const unsigned short *bmp, int x, int y)
{
	unsigned long line;
	char i, shift, begin=0, end=16, *screen, *p=(char*)&line+1;
	if(!bmp || x<0 || x>112 || y<-15 || y>63) return;
	if(y < 0) begin = -y;
	if(y > 48) end = 64-y;
	shift = 8-(x&7);
	screen = ML_vram_adress()+(y+begin<<4)+(x>>3);
	for(i=begin ; i<end ; i++)
	{
		line = bmp[i]<<shift;
		screen[0] ^= *p;
		screen[1] ^= *(p+1);
		if(shift!=8) screen[2] ^= *(p+2);
		screen += 16;
	}
}
#endif

#ifdef ML_BMP_16_OR_CL
void ML_bmp_16_or_cl(const unsigned short *bmp, int x, int y)
{
	unsigned long line;
	char i, shift, begin=0, end=16, bool1=1, bool2=1, bool3=1, *screen, *p=(char*)&line+1;
	if(!bmp || x<-15 || x>127 || y<-15 || y>63) return;
	if(y < 0) begin = -y;
	if(y > 48) end = 64-y;
	shift = 8-(x&7);
	if(x < 0) bool1 = 0;
	if(x<-8 || x>119) bool2 = 0;
	if(x>111 || shift==8) bool3 = 0;
	screen = ML_vram_adress()+(y+begin<<4)+(x>>3);
	for(i=begin ; i<end ; i++)
	{
		line = bmp[i]<<shift;
		if(bool1) screen[0] |= *p;
		if(bool2) screen[1] |= *(p+1);
		if(bool3) screen[2] |= *(p+2);
		screen += 16;
	}
}
#endif

#ifdef ML_BMP_16_AND_CL
void ML_bmp_16_and_cl(const unsigned short *bmp, int x, int y)
{
	unsigned long line;
	char i, shift, begin=0, end=16, bool1=1, bool2=1, bool3=1, *screen, *p=(char*)&line+1;
	if(!bmp || x<-15 || x>127 || y<-15 || y>63) return;
	if(y < 0) begin = -y;
	if(y > 48) end = 64-y;
	shift = 8-(x&7);
	if(x < 0) bool1 = 0;
	if(x<-8 || x>119) bool2 = 0;
	if(x>111 || shift==8) bool3 = 0;
	screen = ML_vram_adress()+(y+begin<<4)+(x>>3);
	for(i=begin ; i<end ; i++)
	{
		line = ~((unsigned short)~bmp[i]<<shift);
		if(bool1) screen[0] &= *p;
		if(bool2) screen[1] &= *(p+1);
		if(bool3) screen[2] &= *(p+2);
		screen += 16;
	}
}
#endif

#ifdef ML_BMP_16_XOR_CL
void ML_bmp_16_xor_cl(const unsigned short *bmp, int x, int y)
{
	unsigned long line;
	char i, shift, begin=0, end=16, bool1=1, bool2=1, bool3=1, *screen, *p=(char*)&line+1;
	if(!bmp || x<-15 || x>127 || y<-15 || y>63) return;
	if(y < 0) begin = -y;
	if(y > 48) end = 64-y;
	shift = 8-(x&7);
	if(x < 0) bool1 = 0;
	if(x<-8 || x>119) bool2 = 0;
	if(x>111 || shift==8) bool3 = 0;
	screen = ML_vram_adress()+(y+begin<<4)+(x>>3);
	for(i=begin ; i<end ; i++)
	{
		line = bmp[i]<<shift;
		if(bool1) screen[0] ^= *p;
		if(bool2) screen[1] ^= *(p+1);
		if(bool3) screen[2] ^= *(p+2);
		screen += 16;
	}
}
#endif

