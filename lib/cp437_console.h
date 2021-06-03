#include "font.h"





/******************************************************************************/
/* CONSTANTS :                                                                */
/******************************************************************************/
#define JAPANESE_FONT_CP437_OFFSET          1000
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

#define MAX_VERTICES                        64

#define MAX_SPRITES                         128





/******************************************************************************/
/* DATA TYPES :                                                               */
/******************************************************************************/

/* ---=== FOR THE PIXEL ARRAY : ===--- */
extern  void *(*drb_symbol_lookup)(const char *sym);
typedef void (*drb_upload_pixel_array_fn)(const char *name,const int w,const int h,const Uint32 *pixels);

/* ---=== CONSOLE RELATED : ===--- */
typedef struct Glyph {
  Uint32  foreground;
  Uint32  background;
  //Uint8   index;
  Uint32  index;
} Glyph;

typedef struct GraphicContext {
  Font*   font;

  Uint32  index;
  Uint32  foreground;
  Uint32  background;

  Uint32  clear_index;
  Uint32  clear_foreground;
  Uint32  clear_background;

  bool    should_draw_index;
  bool    should_draw_foreground;
  bool    should_draw_background;

  Uint32  window_top_left_index;
  Uint32  window_top_right_index;
  Uint32  window_bottom_left_index;
  Uint32  window_bottom_right_index;
  Uint32  window_top_bottom_index;
  Uint32  window_left_right_index;
} GraphicContext;

typedef struct Sprite {
  Uint32  width;
  Uint32  height;
  Uint32* indices;
  Uint32* foregrounds;
  Uint32* backgrounds;
} Sprite;

typedef struct Console {
  // Fonts :
  Uint8                     fonts_count;
  Font**                    fonts;

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
  Uint32                    *vertices;
  size_t                    vertex_count;

  // Sprites :
  Sprite                    *sprites;
  size_t                    sprite_count;

  drb_upload_pixel_array_fn drb_upload_pixel_array;
} Console;





/******************************************************************************/
/* FUNCTION PROTOTYPES :                                                      */
/******************************************************************************/

// --- Creator and Destructor :
Console*  init_console(Uint32 width,Uint32 height,char* font_name,Glyph init_glyph);
void      free_console(Console* console);

// --- Update :
void update_console(Console* console);

// --- Geometry Management :
int   get_console_width(Console* console);
int   get_console_height(Console* console);
int   get_console_pixel_width(Console* console);
int   get_console_pixel_height(Console* console);
void  resize_console(Console* console,Uint32 width,Uint32 height);

// --- Font Management :
Font* get_font_by_name(Console* console,char* font_name);
Font  get_current_font(Console* console);
void  set_gc_font(Console* console,char* const font_name);

// --- Graphic Context :
void set_gc_index(Console* console,Uint32 index);
void set_gc_foreground(Console* console,Uint32 foreground);
void set_gc_background(Console* console,Uint32 background);
void set_gc_clear_index(Console* console,Uint32 index);
void set_gc_clear_foreground(Console* console,Uint32 foreground);
void set_gc_clear_background(Console* console,Uint32 background);
void window_top_left_index(Console* console,Uint32 index);
void window_top_right_index(Console* console,Uint32 index);
void window_bottom_left_index(Console* console,Uint32 index);
void window_bottom_right_index(Console* console,Uint32 index);
void window_top_bottom_index(Console* console,Uint32 index);
void window_left_right_index(Console* console,Uint32 index);

// --- DRAWING :
// --- Clearing the console :
void clear_console(Console* console);

// --- Single Glyphs :
Glyph get_glyph_at(Console* console,Uint32 x,Uint32 y);
void  draw_glyph_at(Console* console,Uint32 x,Uint32 y);

// --- Strings :
void draw_string_at(Console* console,char* const string,Uint32 x,Uint32 y);
void draw_cp437_string_with_japanese_font_at(Console* console,char* const string,Uint32 x,Uint32 y);

// --- Lines :
void draw_horizontal_line(Console* console,Uint32 x1,Uint32 x2,Uint32 y);
void draw_vertical_line(Console* console,Uint32 x,Uint32 y1,Uint32 y2);
void draw_line(Console* console,Uint32 x1,Uint32 y1,Uint32 x2,Uint32 y2);
void draw_antialiased_line(Console* console,Uint32 x1,Uint32 y1,Uint32 x2,Uint32 y2);

// --- Rectangles :
void stroke_rectangle(Console* console,Uint32 x,Uint32 y,Uint32 width,Uint32 height);
void fill_rectangle(Console* console,Uint32 x,Uint32 y,Uint32 width,Uint32 height);

// --- Windows :
void draw_window(Console* console,Uint32 x,Uint32 y,Uint32 width,Uint32 height);
void draw_thin_window(Console* console,Uint32 x,Uint32 y,Uint32 width,Uint32 height);
void draw_thick_window(Console* console,Uint32 x,Uint32 y,Uint32 width,Uint32 height);

// --- Convex Polygons :
Uint32* get_polygon_vertices_array(Console* console);
void    set_polygon_vertex_count(Console* console,size_t count);
void    fill_polygon(Console* console);

// --- Sprites :
Sprite  create_sprite(Console* console,Uint32 width,Uint32 height);
void    free_sprite(Console* console,Sprite* sprite);
size_t  get_sprite_count(Console* console);
void    draw_sprite_at(Console* console,size_t sprite_index,Uint32 x,Uint32 y);
