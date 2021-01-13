#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
//#include "cp437_8x8.h"
#include <dragonruby.h>
#include "cp437_console.h"





/******************************************************************************/
/* CONSTANTS :                                                                */
/******************************************************************************/
#define GLYPH_PIXEL_WIDTH                   8
#define GLYPH_PIXEL_HEIGHT                  8

#define LINE_BOTTOM_LEFT_TO_TOP_RIGHT_GLYPH 47
#define LINE_TOP_LEFT_TO_BOTTOM_RIGHT_GLYPH 92
#define LINE_HORIZONTAL_GLYPH               45
#define LINE_VERTICAL_GLYPH                 179

#define THIN_WINDOW_TOP_LEFT_INDEX          218
#define THIN_WINDOW_TOP_RIGHT_INDEX         191
#define THIN_WINDOW_BOTTOM_LEFT_INDEX       192
#define THIN_WINDOW_BOTTOM_RIGHT_INDEX      217
#define THIN_WINDOW_TOP_BOTTOM_INDEX        196
#define THIN_WINDOW_LEFT_RIGHT_INDEX        179

#define THICK_WINDOW_TOP_LEFT_INDEX         201
#define THICK_WINDOW_TOP_RIGHT_INDEX        187
#define THICK_WINDOW_BOTTOM_LEFT_INDEX      200
#define THICK_WINDOW_BOTTOM_RIGHT_INDEX     188
#define THICK_WINDOW_TOP_BOTTOM_INDEX       205
#define THICK_WINDOW_LEFT_RIGHT_INDEX       186





/******************************************************************************/
/* DATA TYPES :                                                               */
/******************************************************************************/

/* ---=== GENERAL : ===--- */
//typedef unsigned char Uint8;
//typedef unsigned int  Uint32;

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
  Font*   font;

  Uint32  background;
  Uint32  foreground;
  Uint8   index;

  Uint32  clear_background;
  Uint32  clear_foreground;
  Uint8   clear_index;

  bool    should_draw_background;
  bool    should_draw_foreground;
  bool    should_draw_index;

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
  Uint32*                   left_scan;
  Uint32*                   right_scan;
  drb_upload_pixel_array_fn drb_upload_pixel_array;
} Console;





/******************************************************************************/
/* FUNCTION PROTOTYPES :                                                      */
/******************************************************************************/
Font* get_font_by_name(char* font_name);
//void print_console_pixels(void);
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
void init_console(Uint32 width,Uint32 height,char* font_name, Glyph init_glyph) {
  // --- Creating the console :
  console         = (Console *)malloc(sizeof(Console));

  // --- Setting the console's dimensions :
  console->width  = width;
  console->height = height;

  // --- Setting the console's glyph array :
  console->size   = width * height;
  console->glyphs = (Glyph*)calloc(console->size, sizeof(Glyph));

  // --- Setting the graphic context :
  console->graphic_context.font                       = get_font_by_name(font_name);

  console->graphic_context.background                 = init_glyph.background;
  console->graphic_context.foreground                 = init_glyph.foreground;
  console->graphic_context.index                      = init_glyph.index;

  console->graphic_context.clear_background           = init_glyph.background;
  console->graphic_context.clear_foreground           = init_glyph.foreground;
  console->graphic_context.clear_index                = init_glyph.index;

  console->graphic_context.should_draw_background     = true;
  console->graphic_context.should_draw_foreground     = true;
  console->graphic_context.should_draw_index          = true;

  console->graphic_context.window_top_left_index      = THICK_WINDOW_TOP_LEFT_INDEX;
  console->graphic_context.window_top_right_index     = THICK_WINDOW_TOP_RIGHT_INDEX;
  console->graphic_context.window_bottom_left_index   = THICK_WINDOW_BOTTOM_LEFT_INDEX;
  console->graphic_context.window_bottom_right_index  = THICK_WINDOW_BOTTOM_RIGHT_INDEX;
  console->graphic_context.window_top_bottom_index    = THICK_WINDOW_TOP_BOTTOM_INDEX;
  console->graphic_context.window_left_right_index    = THICK_WINDOW_LEFT_RIGHT_INDEX;

  // --- Setting the console's pixel array :
  console->pixel_width  = width  * GLYPH_PIXEL_WIDTH;
  console->pixel_height = height * GLYPH_PIXEL_HEIGHT;
  console->pixels       = (Uint32*)calloc(console->pixel_width * console->pixel_height, sizeof(Uint32));

  for(size_t i = 0; i < height; i+=1) {
    for(size_t j = 0; j < width; j+=1) {
      draw_glyph_at(j, i);
    }
  }

  // --- Miscellaneous :
  console->left_scan  = (Uint32*)malloc(height * sizeof(Uint32));
  console->right_scan = (Uint32*)malloc(height * sizeof(Uint32));

  console->drb_upload_pixel_array = drb_symbol_lookup("drb_upload_pixel_array");
}

Font* get_font_by_name(char* font_name) {
  for(size_t i = 0; i < fonts_count; i += 1) {
    if(strcmp(fonts[i]->name, font_name) == 0)
      return fonts[i];
  }

  return NULL;
}

//void print_console_pixels(void) {
//  for(size_t i = 0; i < console->height * GLYPH_PIXEL_HEIGHT; i+=1) {
//    for(size_t j = 0; j < console->width * GLYPH_PIXEL_WIDTH; j+=1) {
//      printf("%u,", console->pixels[i * console->width * GLYPH_PIXEL_WIDTH + j]);
//    }
//    printf("\n");
//  }
//}

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
void set_gc_clear_background(Uint32 background) {
  console->graphic_context.clear_background = background;
}

DRB_FFI
void set_gc_clear_foreground(Uint32 foreground) {
  console->graphic_context.clear_foreground = foreground;
}

DRB_FFI
void set_gc_clear_index(Uint8 index) {
  console->graphic_context.clear_index = index;
}


/* ---=== DRAWING : ===--- */

// --- Clearing the console :
DRB_FFI
void clear_console(void) {
  for(size_t y = 0; y < console->height; y+=1) {
    for(size_t x = 0; x < console->width; x+=1) {
      Uint32 x_offset = x * GLYPH_PIXEL_WIDTH;
      Uint32 y_offset = y * GLYPH_PIXEL_HEIGHT;

      for(size_t i = 0; i < GLYPH_PIXEL_HEIGHT; i+=1 ) {
        //Uint8 line = cp437_8x8[console->graphic_context.clear_index][i];
        Uint8 index = console->graphic_context.clear_index;
        Uint8 line  = *(console->graphic_context.font->glyph_data + FONTS_MAX_WIDTH * sizeof(Uint8) * index + i);

        for(size_t j = 0; j < GLYPH_PIXEL_WIDTH; j+=1) {
          Uint32 pixel_index            = ( y_offset + i ) * console->pixel_width + x_offset + j;
          console->pixels[pixel_index]  = ((line >> j) & 1 ) == true ? console->graphic_context.clear_foreground : console->graphic_context.clear_background;
        }
      }
    }
  }
}


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
    //Uint8 line = cp437_8x8[console->glyphs[glyph_offset].index][i];
    Uint8 index = console->glyphs[glyph_offset].index;
    Uint8 line  = *(console->graphic_context.font->glyph_data + FONTS_MAX_WIDTH * sizeof(Uint8) * index + i);
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
  if (dx == 0) {  // vertical line
    draw_vertical_line(x1, y1, y2);
    return;
  }

  if (dy == 0) {  // horizontal line
    draw_horizontal_line(x1, x2, y1);
    return;
  }

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

DRB_FFI
void draw_antialiased_line(Uint32 x1,Uint32 y1,Uint32 x2,Uint32 y2) {
  int     x, y, dx, dy, x_increment, y_increment, d;
  Uint8   step_index, previous_index;
  float   tan;

  // Set-up of the bresenham algorythm :
  x = x1;
  y = y1;

  dx = x2 - x1;
  dy = y2 - y1;

  x_increment = ( dx > 0 ) ? 1 : -1 ;
  y_increment = ( dy > 0 ) ? 1 : -1 ;


  // Edge cases :
  if (dx == 0) {  // vertical line
    previous_index                  = console->graphic_context.index;
    console->graphic_context.index  = LINE_VERTICAL_GLYPH;
    draw_vertical_line(x1, y1, y2);
    console->graphic_context.index  = previous_index;
    return;
  }

  if (dy == 0) {  // horizontal line
    previous_index                  = console->graphic_context.index;
    console->graphic_context.index  = LINE_HORIZONTAL_GLYPH;
    draw_horizontal_line(x1, x2, y1);
    console->graphic_context.index  = previous_index;
    return;
  }

  // Chosing the "stepping" glyph :
  if (dx > 0)
    step_index = dy < 0 ? LINE_BOTTOM_LEFT_TO_TOP_RIGHT_GLYPH : LINE_TOP_LEFT_TO_BOTTOM_RIGHT_GLYPH;
  else
    step_index = dy < 0 ? LINE_TOP_LEFT_TO_BOTTOM_RIGHT_GLYPH : LINE_BOTTOM_LEFT_TO_TOP_RIGHT_GLYPH;

  dx = abs(dx);
  dy = abs(dy);


  // Drawing the line :
  previous_index  = console->graphic_context.index;

  // First Point :
  tan = fabsf( ((float)dy)/dx );

  if ( ( tan > 0.08 ) && ( tan < 5.67 ) )
    console->graphic_context.index  = step_index;
  else {
    if (dx > dy)
      console->graphic_context.index  = LINE_HORIZONTAL_GLYPH;
    else
      console->graphic_context.index  = LINE_VERTICAL_GLYPH;
  }

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

        console->graphic_context.index  = step_index;
        draw_glyph_at(x, y);
      }
      else {
        console->graphic_context.index  = LINE_HORIZONTAL_GLYPH;

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
        console->graphic_context.index  = step_index;
      }
      else
        console->graphic_context.index  = LINE_VERTICAL_GLYPH;

      draw_glyph_at(x, y);
    }
  }

  console->graphic_context.index  = previous_index;
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

DRB_FFI
void draw_thin_window(Uint32 x,Uint32 y,Uint32 width,Uint32 height) {
  Uint8 previous_index  = console->graphic_context.index;

  console->graphic_context.index = THIN_WINDOW_TOP_LEFT_INDEX;
  draw_glyph_at(x, y);

  console->graphic_context.index = THIN_WINDOW_TOP_RIGHT_INDEX;
  draw_glyph_at(x + width - 1, y);

  console->graphic_context.index = THIN_WINDOW_BOTTOM_LEFT_INDEX;
  draw_glyph_at(x, y + height - 1);

  console->graphic_context.index = THIN_WINDOW_BOTTOM_RIGHT_INDEX;
  draw_glyph_at(x + width - 1, y + height - 1);

  console->graphic_context.index = THIN_WINDOW_TOP_BOTTOM_INDEX;
  for(size_t i = x + 1; i < x + width - 1; i += 1) {
    draw_glyph_at(i, y);
    draw_glyph_at(i, y + height - 1);
  }

  console->graphic_context.index = THIN_WINDOW_LEFT_RIGHT_INDEX;
  for(size_t i = y + 1; i < y + height - 1; i += 1) {
    draw_glyph_at(x, i);
    draw_glyph_at(x + width - 1, i);
  }

  console->graphic_context.index  = previous_index;
}

DRB_FFI
void draw_thick_window(Uint32 x,Uint32 y,Uint32 width,Uint32 height) {
  Uint8 previous_index  = console->graphic_context.index;

  console->graphic_context.index = THICK_WINDOW_TOP_LEFT_INDEX;
  draw_glyph_at(x, y);

  console->graphic_context.index = THICK_WINDOW_TOP_RIGHT_INDEX;
  draw_glyph_at(x + width - 1, y);

  console->graphic_context.index = THICK_WINDOW_BOTTOM_LEFT_INDEX;
  draw_glyph_at(x, y + height - 1);

  console->graphic_context.index = THICK_WINDOW_BOTTOM_RIGHT_INDEX;
  draw_glyph_at(x + width - 1, y + height - 1);

  console->graphic_context.index = THICK_WINDOW_TOP_BOTTOM_INDEX;
  for(size_t i = x + 1; i < x + width - 1; i += 1) {
    draw_glyph_at(i, y);
    draw_glyph_at(i, y + height - 1);
  }

  console->graphic_context.index = THICK_WINDOW_LEFT_RIGHT_INDEX;
  for(size_t i = y + 1; i < y + height - 1; i += 1) {
    draw_glyph_at(x, i);
    draw_glyph_at(x + width - 1, i);
  }

  console->graphic_context.index  = previous_index;
}

// --- Polygons :
void scan_polygon_left_edge(float x1,float y1,float x2,float y2) {
  int    y, y_top, y_bottom;
  float  islope, x;

  // Escape horizontal lines :
  //if ( y1 == y2 )
  if ( fabsf( y1 - y2 ) < 0.75 )
    return;


  // Calculating useful values for the scanning loop :
  islope    = ( x2 - x1 ) / ( y2 - y1 );

  y_top     = y1 > 0.5 ? (int)( y1 - 0.5 ) : 0;
  y_bottom  = (int)( y2 + 0.5 );

  x         = ( y_top + 0.5 - y1 ) * islope + x1;     // + 0.5 : the scan line goes through the middle of the pixel


  // Scan converting :
  for ( y = y_top; y >= y_bottom; y -= 1 ) {
    console->left_scan[y] = (int)( x + 0.5 );
    x -= islope;
  }

}

void scan_polygon_right_edge(float x1, float y1, float x2, float y2) {
  int    y, y_top, y_bottom;
  float  islope, x;

  // Escape horizontal lines :
  //if ( y1 == y2 )
  if ( fabsf( y1 - y2 ) < 0.75 )
    return;


  // Calculating useful values for the scanning loop :
  islope    = ( x2 - x1 ) / ( y2 - y1 );

  y_top     = y1 > 0.5 ? (int)( y1 - 0.5 ) : 0;
  y_bottom  = (int)( y2 + 0.5 );

  x         = ( y_top + 0.5 - y1 ) * islope + x1;     // + 0.5 : the scan line goes through the middle of the pixel


  // Scan converting :
  for ( y = y_top; y >= y_bottom; y -= 1) {
    console->right_scan[y] = x > 0.5 ? (int)( x - 0.5 ) : 0;
    x -= islope;
  }

}

