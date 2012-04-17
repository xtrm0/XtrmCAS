/*************************************************************/
/** MonochromeLib - monochrome graphic library for fx-9860G **/
/** MonochromeLib is free software                          **/
/**                                                         **/
/** @author Pierre "PierrotLL" Le Gall                      **/
/** @contact legallpierre89@gmail.com                       **/
/**                                                         **/
/** @file MonochromeLib.h                                   **/
/** Include header for MonochromeLib                        **/
/**                                                         **/
/** @date 11-22-2011                                        **/
/*************************************************************/

#ifndef MONOCHROMELIB
#define MONOCHROMELIB

/****************************************************/
/** uncomment #define of functions you want to use **/
/****************************************************/

// #define ML_ALL //Auto define all functions

#define ML_CLEAR_VRAM
// #define ML_CLEAR_SCREEN
#define ML_DISPLAY_VRAM

// #define ML_SET_CONTRAST
// #define ML_GET_CONTRAST

// #define ML_PIXEL
// #define ML_POINT
// #define ML_PIXEL_TEST

// #define ML_LINE
// #define ML_HORIZONTAL_LINE
// #define ML_VERTICAL_LINE

// #define ML_RECTANGLE

// #define ML_POLYGON
// #define ML_FILLED_POLYGON

// #define ML_CIRCLE
// #define ML_FILLED_CIRCLE

// #define ML_ELLIPSE
// #define ML_ELLIPSE_IN_RECT
// #define ML_FILLED_ELLIPSE
// #define ML_FILLED_ELLIPSE_IN_RECT

// #define ML_HORIZONTAL_SCROLL
#define ML_VERTICAL_SCROLL

// #define ML_BMP_OR
// #define ML_BMP_AND
// #define ML_BMP_XOR
// #define ML_BMP_OR_CL
// #define ML_BMP_AND_CL
// #define ML_BMP_XOR_CL

// #define ML_BMP_8_OR
// #define ML_BMP_8_AND
// #define ML_BMP_8_XOR
// #define ML_BMP_8_OR_CL
// #define ML_BMP_8_AND_CL
// #define ML_BMP_8_XOR_CL

// #define ML_BMP_16_OR
// #define ML_BMP_16_AND
// #define ML_BMP_16_XOR
// #define ML_BMP_16_OR_CL
// #define ML_BMP_16_AND_CL
// #define ML_BMP_16_XOR_CL


/**************************/
/** Functions prototypes **/
/**************************/

#ifdef __cplusplus
extern "C" {
#endif

#define ML_SCREEN_WIDTH     128
#define ML_SCREEN_HEIGHT    64

#define ML_CONTRAST_MIN     130
#define ML_CONTRAST_NORMAL  168
#define ML_CONTRAST_MAX     190
typedef enum {ML_TRANSPARENT=-1, ML_WHITE, ML_BLACK, ML_XOR, ML_CHECKER} ML_Color;

char* ML_vram_adress();

void ML_clear_vram();
void ML_clear_screen();
void ML_display_vram();

void ML_set_contrast(unsigned char contrast);
unsigned char ML_get_contrast();

void ML_pixel(int x, int y, ML_Color color);
void ML_point(int x, int y, int width, ML_Color color);
ML_Color ML_pixel_test(int x, int y);

void ML_line(int x1, int y1, int x2, int y2, ML_Color color);
void ML_horizontal_line(int y, int x1, int x2, ML_Color color);
void ML_vertical_line(int x, int y1, int y2, ML_Color color);

void ML_rectangle(int x1, int y1, int x2, int y2, int border_width, ML_Color border_color, ML_Color fill_color);

void ML_polygon(const int *x, const int *y, int nb_vertices, ML_Color color);
void ML_filled_polygon(const int *x, const int *y, int nb_vertices, ML_Color color);

void ML_circle(int x, int y, int radius, ML_Color color);
void ML_filled_circle(int x, int y, int radius, ML_Color color);

void ML_ellipse(int x, int y, int radius1, int radius2, ML_Color color);
void ML_ellipse_in_rect(int x1, int y1, int x2, int y2, ML_Color color);
void ML_filled_ellipse(int x, int y, int radius1, int radius2, ML_Color color);
void ML_filled_ellipse_in_rect(int x, int y, int radius1, int radius2, ML_Color color);

void ML_horizontal_scroll(int scroll);
void ML_vertical_scroll(int scroll);

void ML_bmp_or(const unsigned char *bmp, int x, int y, int width, int height);
void ML_bmp_and(const unsigned char *bmp, int x, int y, int width, int height);
void ML_bmp_xor(const unsigned char *bmp, int x, int y, int width, int height);
void ML_bmp_or_cl(const unsigned char *bmp, int x, int y, int width, int height);
void ML_bmp_and_cl(const unsigned char *bmp, int x, int y, int width, int height);
void ML_bmp_xor_cl(const unsigned char *bmp, int x, int y, int width, int height);

void ML_bmp_8_or(const unsigned char *bmp, int x, int y);
void ML_bmp_8_and(const unsigned char *bmp, int x, int y);
void ML_bmp_8_xor(const unsigned char *bmp, int x, int y);
void ML_bmp_8_or_cl(const unsigned char *bmp, int x, int y);
void ML_bmp_8_and_cl(const unsigned char *bmp, int x, int y);
void ML_bmp_8_xor_cl(const unsigned char *bmp, int x, int y);

void ML_bmp_16_or(const unsigned short *bmp, int x, int y);
void ML_bmp_16_and(const unsigned short *bmp, int x, int y);
void ML_bmp_16_xor(const unsigned short *bmp, int x, int y);
void ML_bmp_16_or_cl(const unsigned short *bmp, int x, int y);
void ML_bmp_16_and_cl(const unsigned short *bmp, int x, int y);
void ML_bmp_16_xor_cl(const unsigned short *bmp, int x, int y);

#ifdef __cplusplus
}
#endif


#endif //MONOCHROMELIB
