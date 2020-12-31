#include "cp437_8x8.h"
#include <dragonruby.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>





/******************************************************************************/
/* CONSTANTS :                                                                */
/******************************************************************************/
#define GLYPH_PIXEL_WIDTH   8
#define GLYPH_PIXEL_HEIGHT  8





/******************************************************************************/
/* DATA TYPES :                                                               */
/******************************************************************************/

/* ---=== GENERAL : ===--- */
typedef unsigned char Uint8;
typedef unsigned int  Uint32;

/* ---=== FOR THE PIXEL ARRAY : ===--- */
extern void *(*drb_symbol_lookup)(const char *sym);
typedef void (*drb_upload_pixel_array_fn)(const char *name,const int w,const int h,const Uint32 *pixels);

/* ---=== CONSOLE RELATED : ===--- */
typedef struct Glyph {
  Uint32  foreground;
  Uint32  background;
  Uint8   index;
} Glyph;

typedef struct Console {
  Uint32                    width;          // in glyphs
  Uint32                    height;         // in glyphs
  Glyph*                    glyphs;
  Uint32                    size;
  Uint32                    pixel_width;    // in pixels, obviously
  Uint32                    pixel_height;   // in pixels, obviously
  Uint32*                   pixels;
  drb_upload_pixel_array_fn drb_upload_pixel_array;
} Console;





/******************************************************************************/
/* FUNCTION PROTOTYPES :                                                      */
/******************************************************************************/
void print_console_pixels(void);
void draw_glyph_at(Glyph glyph,Uint32 x,Uint32 y);





/******************************************************************************/
/* GLOBAL VARIABLES :                                                         */
/******************************************************************************/
Console *console;





/******************************************************************************/
/* FUNCTIONS :                                                                */
/******************************************************************************/

/* ---=== CREATOR AND DESTRUCTOR : ===--- */
DRB_FFI
void init_console(Uint32 width,Uint32 height,Glyph init_glyph) {
  // --- Creating the console :
  console         = (Console *)malloc(sizeof(Console));

  // --- Setting the console's dimensions :
  console->width  = width;
  console->height = height;

  // --- Setting the console's glyph array :
  console->size   = width * height;
  console->glyphs = (Glyph*)calloc(console->size, sizeof(Glyph));

  for(size_t i = 0; i < console->size; i+=1) {
    console->glyphs[i].index      = init_glyph.index; 
    console->glyphs[i].background = init_glyph.background;
    console->glyphs[i].foreground = init_glyph.foreground;
  }

  // --- Setting the console's pixel array :
  console->pixel_width  = width  * GLYPH_PIXEL_WIDTH;
  console->pixel_height = height * GLYPH_PIXEL_HEIGHT;
  console->pixels       = (Uint32*)calloc(console->pixel_width * console->pixel_height, sizeof(Uint32));

  for(size_t i = 0; i < height; i+=1) {
    for(size_t j = 0; j < width; j+=1) {
      draw_glyph_at(console->glyphs[i * width + j], j, i);
    }
  }
  console->drb_upload_pixel_array = drb_symbol_lookup("drb_upload_pixel_array");
}

void print_console_pixels(void) {
  for(size_t i = 0; i < console->height * GLYPH_PIXEL_HEIGHT; i+=1) {
    for(size_t j = 0; j < console->width * GLYPH_PIXEL_WIDTH; j+=1) {
      printf("%u,", console->pixels[i * console->width * GLYPH_PIXEL_WIDTH + j]);
    }
    printf("\n");
  }
}

DRB_FFI
void delete_console(void) {
  free(console->glyphs);
  free(console);
}


/* ---=== ACCESSORS : ===--- */
DRB_FFI
int get_console_width(void) {
  return console->width;
}

DRB_FFI
int get_console_height(void) {
  return console->height;
}

DRB_FFI
Glyph get_glyph_at(Uint32 x,Uint32 y) {
  int index = x + console->width * y;
  return console->glyphs[index];
}

DRB_FFI
int get_console_pixel_width(void) {
  return GLYPH_PIXEL_WIDTH * console->width;
}

DRB_FFI
int get_console_pixel_height(void) {
  return GLYPH_PIXEL_HEIGHT * console->height;
}


/* ---=== DRAWING : ===--- */
DRB_FFI
void draw_glyph_at(Glyph glyph,Uint32 x,Uint32 y) {
  Uint32 x_offset = x * GLYPH_PIXEL_WIDTH;
  Uint32 y_offset = y * GLYPH_PIXEL_HEIGHT;

  for(size_t i = 0; i < GLYPH_PIXEL_HEIGHT; i+=1 ) {
    char line = cp437_8x8[glyph.index][i];
    for(size_t j = 0; j < GLYPH_PIXEL_WIDTH; j+=1) {
      Uint32 pixel_index            = ( y_offset + i ) * console->pixel_width + x_offset + j;
      console->pixels[pixel_index]  = ((line >> j) & 1 ) == true ? glyph.foreground : glyph.background;
    }
  }
}


DRB_FFI
void update_console(void) {
  console->drb_upload_pixel_array("console", console->pixel_width, console->pixel_height, console->pixels);
}
