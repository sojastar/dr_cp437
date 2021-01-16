#include "cp437_8x8.h"
#include "cp437_8x14.h"
#include "cp437_8x16.h"





/******************************************************************************/
/* CONSTANTS :                                                                */
/******************************************************************************/
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

// --- Creator and Destructor :
void init_console(Uint32 width,Uint32 height,char* font_name,Glyph init_glyph);
void delete_console(void);

// --- Update :
void update_console(void);

// --- Geometry Management :
int get_console_width(void);
int get_console_height(void);
int get_console_pixel_width(void);
int get_console_pixel_height(void);
void resize_console(Uint32 width,Uint32 height);

// --- Font Management :
Font* get_font_by_name(char* font_name);
Font get_current_font(void);
void set_gc_font(char* const font_name);

// --- Graphic Context :
void set_gc_index(Uint8 index);
void set_gc_background(Uint32 background);
void set_gc_foreground(Uint32 foreground);
void set_gc_clear_background(Uint32 background);
void set_gc_clear_foreground(Uint32 foreground);
void set_gc_clear_index(Uint8 index);

// --- DRAWING :
// --- Clearing the console :
void clear_console(void);

// --- Single Glyphs :
Glyph get_glyph_at(Uint32 x,Uint32 y);
void draw_glyph_at(Uint32 x,Uint32 y);

// --- Lines :
void draw_horizontal_line(Uint32 x1,Uint32 x2,Uint32 y);
void draw_vertical_line(Uint32 x,Uint32 y1,Uint32 y2);
void draw_line(Uint32 x1,Uint32 y1,Uint32 x2,Uint32 y2);
void draw_antialiased_line(Uint32 x1,Uint32 y1,Uint32 x2,Uint32 y2);

// --- Rectangles :
void stroke_rectangle(Uint32 x,Uint32 y,Uint32 width,Uint32 height);
void fill_rectangle(Uint32 x,Uint32 y,Uint32 width,Uint32 height);

// --- Windows :
void draw_window(Uint32 x,Uint32 y,Uint32 width,Uint32 height);
void draw_thin_window(Uint32 x,Uint32 y,Uint32 width,Uint32 height);
void draw_thick_window(Uint32 x,Uint32 y,Uint32 width,Uint32 height);





/******************************************************************************/
/* GLOBAL VARIABLES :                                                         */
/******************************************************************************/
Uint8 fonts_count = 3;
Font* fonts[]     = { &cp437_8x8,
                      &cp437_8x14,
                      &cp437_8x16 };

Console *console;
