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

typedef struct GraphicContext {
  Uint32  background;
  Uint32  foreground;
  Uint8   index;

  bool    should_draw_background;
  bool    should_draw_foreground;
  bool    should_draw_index;

  bool    antialiased;

  Uint8   window_top_left_index;
  Uint8   window_top_right_index;
  Uint8   window_bottom_left_index;
  Uint8   window_bottom_right_index;
  Uint8   window_top_bottom_index;
  Uint8   window_left_right_index;
} GraphicContext;

typedef struct Console {
  // Geometry :
  Uint32                    width;          // in glyphs
  Uint32                    height;         // in glyphs

  // Logical Content :
  Glyph*                    glyphs;
  Uint32                    size;

  // Graphic Content :
  Uint32                    pixel_width;    // in pixels, obviously
  Uint32                    pixel_height;   // in pixels, obviously
  Uint32*                   pixels;

  // Graphic Context :
  GraphicContext            graphic_context;

  // Rendering :
  drb_upload_pixel_array_fn drb_upload_pixel_array;
} Console;





/******************************************************************************/
/* FUNCTION PROTOTYPES :                                                      */
/******************************************************************************/
void print_console_pixels(void);
void draw_glyph_at(Uint32 x,Uint32 y);
void draw_horizontal_line(Uint32 x1,Uint32 x2,Uint32 y);
void draw_vertical_line(Uint32 x,Uint32 y1,Uint32 y2);





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

  // --- Setting the graphic context :
  console->graphic_context.background                 = init_glyph.background;
  console->graphic_context.foreground                 = init_glyph.foreground;
  console->graphic_context.index                      = init_glyph.index;

  console->graphic_context.should_draw_background     = true;
  console->graphic_context.should_draw_foreground     = true;
  console->graphic_context.should_draw_index          = true;

  console->graphic_context.antialiased                = false;

  console->graphic_context.window_top_left_index      = 201;
  console->graphic_context.window_top_right_index     = 187;
  console->graphic_context.window_bottom_left_index   = 200;
  console->graphic_context.window_bottom_right_index  = 188;
  console->graphic_context.window_top_bottom_index    = 205;
  console->graphic_context.window_left_right_index    = 186;

  // --- Setting the console's pixel array :
  console->pixel_width  = width  * GLYPH_PIXEL_WIDTH;
  console->pixel_height = height * GLYPH_PIXEL_HEIGHT;
  console->pixels       = (Uint32*)calloc(console->pixel_width * console->pixel_height, sizeof(Uint32));

  for(size_t i = 0; i < height; i+=1) {
    for(size_t j = 0; j < width; j+=1) {
      draw_glyph_at(j, i);
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
  free(console->pixels);
  free(console);
}


/* ---=== UPDATE : ===--- */
DRB_FFI
void update_console(void) {
  console->drb_upload_pixel_array("console", console->pixel_width, console->pixel_height, console->pixels);
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


/* ---=== GRAPHIC CONTEXT : ===--- */
DRB_FFI
void set_gc_index(Uint8 index) {
  console->graphic_context.index = index;
}

DRB_FFI
void set_gc_background(Uint32 background) {
  console->graphic_context.background = background;
}

DRB_FFI
void set_gc_foreground(Uint32 foreground) {
  console->graphic_context.foreground = foreground;
}

DRB_FFI
void set_gc_antialiased(bool antialiased) {
  console->graphic_context.antialiased = antialiased;
}


/* ---=== DRAWING : ===--- */

// --- Single Glyph :
DRB_FFI
void draw_glyph_at(Uint32 x,Uint32 y) {
  // --- What glyph are we talking about ?
  Uint32 glyph_offset = y * console->width + x;

  // --- Updating the glyphs :
  if (console->graphic_context.should_draw_index)
    console->glyphs[glyph_offset].index       = console->graphic_context.index;
  if (console->graphic_context.should_draw_background)
    console->glyphs[glyph_offset].background  = console->graphic_context.background;
  if (console->graphic_context.should_draw_foreground)
    console->glyphs[glyph_offset].foreground  = console->graphic_context.foreground;

  // --- Drawing the pixels :
  Uint32 x_offset = x * GLYPH_PIXEL_WIDTH;
  Uint32 y_offset = y * GLYPH_PIXEL_HEIGHT;

  for(size_t i = 0; i < GLYPH_PIXEL_HEIGHT; i+=1 ) {
    char line = cp437_8x8[console->glyphs[glyph_offset].index][i];
    for(size_t j = 0; j < GLYPH_PIXEL_WIDTH; j+=1) {
      Uint32 pixel_index            = ( y_offset + i ) * console->pixel_width + x_offset + j;
      console->pixels[pixel_index]  = ((line >> j) & 1 ) == true ? console->glyphs[glyph_offset].foreground : console->glyphs[glyph_offset].background;
    }
  }
}

// --- Lines :
DRB_FFI
void draw_horizontal_line(Uint32 x1,Uint32 x2,Uint32 y) {
  Uint32 start, end;

  if (x1 <= x2) {
    start = x1;
    end   = x2;
  }
  else {
    start = x2;
    end   = x1;
  }

  for(size_t x = start; x <= end; x++)
    draw_glyph_at(x, y);
}

DRB_FFI
void draw_vertical_line(Uint32 x,Uint32 y1,Uint32 y2) {
  Uint32 start, end;

  if (y1 <= y2) {
    start = y1;
    end   = y2;
  }
  else {
    start = y2;
    end   = y1;
  }

  for(size_t y = start; y <= end; y++)
    draw_glyph_at(x, y);
}

DRB_FFI
void draw_line(Uint32 x1,Uint32 y1,Uint32 x2,Uint32 y2) {
  int x, y, dx, dy, x_increment, y_increment, d;

  // Set-up of the bresenham algorythm :
  x = x1;
  y = y1;

  dx = x2 - x1;
  dy = y2 - y1;

  x_increment = ( dx > 0 ) ? 1 : -1 ;
  y_increment = ( dy > 0 ) ? 1 : -1 ;


  // Edge cases :
  if (dx == 0)  // vertical line
    draw_vertical_line(x1, y1, y2);

  if (dy == 0)  // horizontal line
    draw_horizontal_line(x1, y1, y2);

  dx = abs(dx);
  dy = abs(dy);


  // Drawing the line :

  // First Point :
  draw_glyph_at(x1, y1);

  // Rest of the Line :
  if (dx > dy) {

    d = dx / 2;

    for(size_t i = 1; i <= dx; i += 1) {
      x += x_increment;
      d += dy;

      if (d >= dx) {
        d -= dx;
        y += y_increment;
        draw_glyph_at(x, y);
      }
      else {
        if (y_increment < 0)
          draw_glyph_at(x, y);
        else
          draw_glyph_at(x, y + 1);
      }
    }
  }
  else {
    d = dy / 2;

    for(size_t i = 1; i <= dy; i += 1) {
      y += y_increment;
      d += dx;

      if (d >= dy) {
        d -= dy;
        x += x_increment;
      }

      draw_glyph_at(x, y);
    }
  }
}

// --- Rectangles :
DRB_FFI
void stroke_rectangle(Uint32 x,Uint32 y,Uint32 width,Uint32 height) {
  for(size_t i = x; i < x + width; i += 1) {
    draw_glyph_at(i, y);
    draw_glyph_at(i, y + height - 1);
  }
  for(size_t i = y + 1; i < y + height - 1; i += 1) {
    draw_glyph_at(x, i);
    draw_glyph_at(x + width - 1, i);
  }
}

DRB_FFI
void fill_rectangle(Uint32 x,Uint32 y,Uint32 width,Uint32 height) {
  for(size_t i = y; i < y + height - 1; i += 1)
    for(size_t j = x; j < x + width - 1; j += 1)
      draw_glyph_at(j, i);
}

// --- Windows :
DRB_FFI
void draw_window(Uint32 x,Uint32 y,Uint32 width,Uint32 height) {
  Uint8 previous_index  = console->graphic_context.index;

  console->graphic_context.index = console->graphic_context.window_top_left_index;
  draw_glyph_at(x, y);

  console->graphic_context.index = console->graphic_context.window_top_right_index;
  draw_glyph_at(x + width - 1, y);

  console->graphic_context.index = console->graphic_context.window_bottom_left_index;
  draw_glyph_at(x, y + height - 1);

  console->graphic_context.index = console->graphic_context.window_bottom_right_index;
  draw_glyph_at(x + width - 1, y + height - 1);

  console->graphic_context.index = console->graphic_context.window_top_bottom_index;
  for(size_t i = x + 1; i < x + width - 1; i += 1) {
    draw_glyph_at(i, y);
    draw_glyph_at(i, y + height - 1);
  }

  console->graphic_context.index = console->graphic_context.window_left_right_index;
  for(size_t i = y + 1; i < y + height - 1; i += 1) {
    draw_glyph_at(x, i);
    draw_glyph_at(x + width - 1, i);
  }

  console->graphic_context.index  = previous_index;
}
