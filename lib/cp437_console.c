#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <dragonruby.h>
#include "cp437_console.h"





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
  console->pixel_width  = width  * console->graphic_context.font->width;
  console->pixel_height = height * console->graphic_context.font->height;
  console->pixels       = (Uint32*)calloc(console->pixel_width * console->pixel_height, sizeof(Uint32));

  for(size_t i = 0; i < console->height; i+=1)
    for(size_t j = 0; j < console->width; j+=1)
      draw_glyph_at(j, i);

  // --- Miscellaneous :
  console->left_scan    = (Uint32*)calloc(height, sizeof(Uint32));
  console->right_scan   = (Uint32*)calloc(height, sizeof(Uint32));
  console->vertices     = (Uint32*)calloc(2 * MAX_VERTICES, sizeof(Uint32));
  console->vertex_count = 0;

  console->drb_upload_pixel_array = drb_symbol_lookup("drb_upload_pixel_array");
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
  console->drb_upload_pixel_array(  "console",
                                    console->pixel_width,
                                    console->pixel_height,
                                    console->pixels );
}


/* ---=== GEOMETRY MANAGEMENT : ===--- */
DRB_FFI
int get_console_width(void) {
  return console->width;
}

DRB_FFI
int get_console_height(void) {
  return console->height;
}

DRB_FFI
int get_console_pixel_width(void) {
  return console->graphic_context.font->width * console->width;
}

DRB_FFI
int get_console_pixel_height(void) {
  return console->graphic_context.font->height * console->height;
}

DRB_FFI
void resize_console(Uint32 width,Uint32 height) {
  // --- Resetting the console's dimensions :
  console->width  = width;
  console->height = height;

  // --- Resetting the console's glyph array :
  console->size   = width * height;
  console->glyphs = (Glyph*)calloc(console->size, sizeof(Glyph));

  // --- Resetting the console's pixel array :
  console->pixel_width  = width  * console->graphic_context.font->width;
  console->pixel_height = height * console->graphic_context.font->height;
  console->pixels       = (Uint32*)calloc(console->pixel_width * console->pixel_height, sizeof(Uint32));

  clear_console();

  // --- Miscellaneous :
  console->left_scan  = (Uint32*)malloc(height * sizeof(Uint32));
  console->right_scan = (Uint32*)malloc(height * sizeof(Uint32));
}


/* ---=== FONT MANAGEMENT : ===--- */
Font* get_font_by_name(char* font_name) {
  for(size_t i = 0; i < fonts_count; i += 1) {
    if(strcmp(fonts[i]->name, font_name) == 0)
      return fonts[i];
  }

  return NULL;
}

DRB_FFI
Font get_current_font(void) {
  return *(console->graphic_context.font);
}

DRB_FFI
void set_gc_font(char* const font_name) {
  console->graphic_context.font = get_font_by_name(font_name);

  // --- Resetting the console's pixel array :
  free(console->pixels);

  console->pixel_width  = console->width  * console->graphic_context.font->width;
  console->pixel_height = console->height * console->graphic_context.font->height;
  console->pixels       = (Uint32*)calloc(console->pixel_width * console->pixel_height, sizeof(Uint32));

  for(size_t i = 0; i < console->height; i+=1) {
    for(size_t j = 0; j < console->width; j+=1) {
      Glyph glyph = console->glyphs[j + console->width * i];
      console->graphic_context.index      = glyph.index;
      console->graphic_context.foreground = glyph.foreground;
      console->graphic_context.background = glyph.background;
      draw_glyph_at(j, i);
    }
  }
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
  // Saving the current drawing glyph... :
  Uint8   previous_index              = console->graphic_context.index;
  Uint32  previous_foreground         = console->graphic_context.foreground;
  Uint32  previous_background         = console->graphic_context.background;

  // And setting the clear glyph as the current drawing glyph :
  console->graphic_context.index      = console->graphic_context.clear_index;
  console->graphic_context.foreground = console->graphic_context.clear_foreground;
  console->graphic_context.background = console->graphic_context.clear_background;

  // Drawing the clear glyph all over the console :
  for(size_t y = 0; y < console->height; y+=1)
    for(size_t x = 0; x < console->width; x+=1)
      draw_glyph_at(x, y);

  // Restoring the drawing glyph :
  console->graphic_context.index      = previous_index;
  console->graphic_context.foreground = previous_foreground;
  console->graphic_context.background = previous_background;
}


// --- Single Glyphs :
DRB_FFI
Glyph get_glyph_at(Uint32 x,Uint32 y) {
  return console->glyphs[x + console->width * y];
}

DRB_FFI
void draw_glyph_at(Uint32 x,Uint32 y) {
  // --- What glyph are we talking about ?
  Uint32  glyph_offset  = y * console->width + x;

  // --- Updating the glyphs :
  if (console->graphic_context.should_draw_index)
    console->glyphs[glyph_offset].index       = console->graphic_context.index;
  if (console->graphic_context.should_draw_foreground)
    console->glyphs[glyph_offset].foreground  = console->graphic_context.foreground;
  if (console->graphic_context.should_draw_background)
    console->glyphs[glyph_offset].background  = console->graphic_context.background;

  Uint8 index = console->glyphs[glyph_offset].index;

  // --- Drawing the pixels :
  Uint32 x_offset = x * console->graphic_context.font->width;
  Uint32 y_offset = y * console->graphic_context.font->height;

  for(size_t i = 0; i < console->graphic_context.font->height; i+=1 ) {
    Uint8 line  = *(console->graphic_context.font->glyph_data + sizeof(Uint8) * (index * console->graphic_context.font->height + i));
    for(size_t j = 0; j < console->graphic_context.font->width; j+=1) {
      Uint32 pixel_index            = ( y_offset + i ) * console->pixel_width + x_offset + j;
      console->pixels[pixel_index]  = ((line >> j) & 1 ) == true ? console->glyphs[glyph_offset].foreground : console->glyphs[glyph_offset].background;
    }
  }
}


// --- Strings :
DRB_FFI
void draw_string_at(char* const string,Uint32 x,Uint32 y) {
  for(size_t i = 0; i < string[i]; i += 1) {
    set_gc_index((Uint8)string[i]);
    draw_glyph_at(x + i, y);
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
DRB_FFI
Uint32* get_polygon_vertices_array(void) {
  return console->vertices;
}

DRB_FFI
void set_polygon_vertex_count(size_t count) {
  console->vertex_count = count;
}

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


DRB_FFI
void fill_polygon(void) {
  size_t  i;

  // Clearing the rasterizer's buffers :
  for(i = 0; i < console->height; i += 1) {
    console->left_scan[i]   = UINT8_MAX;
    console->right_scan[i]  = 0;
  }


  // Finding the top and bottom of the polygon :

  // Initializing the loop with the first point y value :
  Uint32 max_y_index = 0;
  Uint32 min_y_index = 0;

  Uint32 max_y  = console->vertices[0];
  Uint32 min_y  = console->vertices[1];

  for(i = 1; i < console->vertex_count; i += 1) {

    // Check the bottom :
    if ( console->vertices[2*i+1] < min_y ) {
      min_y       = console->vertices[2*i+1];
      min_y_index = i;
    }

    // Check the top :
    if ( console->vertices[2*i+1] > max_y ) {
      max_y       = console->vertices[2*i+1];
      max_y_index = i;
    }

  }


  // Discard null height polygons :
  if ( min_y == max_y )
    return;


  // Devise the winding order :
  Uint32  previous_point_x  = console->vertices[2*(( max_y_index - 1 + console->vertex_count) % console->vertex_count)];
  Uint32  next_point_x      = console->vertices[2*(( max_y_index + 1 ) % console->vertex_count)];
  int     winding_order     = previous_point_x < next_point_x ? -1 : 1;

  /*printf("winding order: %d\n", winding_order);
  printf("max_y_index: %u\n", max_y_index);
  printf("min_y_index: %u\n", min_y_index);*/
  // Scan the left and right edges of the polygon :

  // Left :
  i = 0;
  while ( console->vertices[2 * ( ( ( max_y_index + i * winding_order ) + console->vertex_count ) % console->vertex_count ) + 1] != min_y ) {
    scan_polygon_left_edge( console->vertices[2 * ( ( ( max_y_index + i * winding_order ) + console->vertex_count ) % console->vertex_count ) ],
                            console->vertices[2 * ( ( ( max_y_index + i * winding_order ) + console->vertex_count ) % console->vertex_count ) + 1],
                            console->vertices[2 * ( ( ( max_y_index + ( i + 1 ) * winding_order ) + console->vertex_count ) % console->vertex_count ) ],
                            console->vertices[2 * ( ( ( max_y_index + ( i + 1 ) * winding_order ) + console->vertex_count ) % console->vertex_count ) + 1] );

    i += 1;
  }

  // Right :
  i = 0;
  while ( console->vertices[2 * ( ( ( max_y_index - i * winding_order ) + console->vertex_count ) % console->vertex_count ) + 1] != min_y ) {
    scan_polygon_right_edge(  console->vertices[2 * ( ( ( max_y_index - i * winding_order ) + console->vertex_count ) % console->vertex_count )],
                              console->vertices[2 * ( ( ( max_y_index - i * winding_order ) + console->vertex_count ) % console->vertex_count ) + 1],
                              console->vertices[2 * ( ( ( max_y_index - ( i + 1 ) * winding_order ) + console->vertex_count ) % console->vertex_count ) ],
                              console->vertices[2 * ( ( ( max_y_index - ( i + 1 ) * winding_order ) + console->vertex_count ) % console->vertex_count ) + 1] );

    i += 1;
  }


  // Draw the polygon :
  for(i = min_y; i < max_y; i += 1)
    draw_horizontal_line(console->left_scan[i], console->right_scan[i], i);
}
