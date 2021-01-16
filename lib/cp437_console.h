#include "cp437_8x8.h"
#include "cp437_8x14.h"
#include "cp437_8x16.h"

Uint8 fonts_count = 3;
Font* fonts[]     = { &cp437_8x8,
                      &cp437_8x14,
                      &cp437_8x16 }; 
