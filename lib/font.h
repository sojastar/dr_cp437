#include "types.h"

#define FONTS_MAX_WIDTH   8
#define FONTS_MAX_HEIGHT  16

#ifndef FONT_DEFINED
#define FONT_DEFINED
typedef struct Font {
  char*   name;
  Uint8   width;
  Uint8   height;
  Uint8   *glyph_data;
} Font;
#endif
