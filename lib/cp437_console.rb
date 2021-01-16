$gtk.ffi_misc.gtk_dlopen("cp437_console")

module CP437
  class Console
    attr_accessor :x, :y,
                  :scale
    attr_reader   :width, :height,
                  :pixel_width, :pixel_height


    # ---=== INITIALIZATION : ===---
    def initialize(x,y,scale,width,height,font,index,background,foreground)
      init_glyph            = FFI::CP437Console::Glyph.new
      init_glyph.index      = index 
      init_glyph.background = CP437::Color::pack_color *background
      init_glyph.foreground = CP437::Color::pack_color *foreground

      FFI::CP437Console::init_console width, height, font, init_glyph

      @x, @y, @scale  = x, y, scale

      @width          = width
      @height         = height

      @pixel_width    = FFI::CP437Console.get_console_pixel_width
      @pixel_height   = FFI::CP437Console.get_console_pixel_height
    end


    # ---=== RENDERING : ===---
    def render(args)
      FFI::CP437Console::update_console

      args.outputs.primitives << [@x,
                                  @y,
                                  @scale * @pixel_width,
                                  @scale * @pixel_height,
                                  :console].sprite
    end


    # ---=== GEOMETRY MANAGEMENT : ===---
    def resize(width,height)
      FFI::CP437Console.resize_console width, height
      @width        = width
      @height       = height
      @pixel_width  = FFI::CP437Console.get_console_pixel_width
      @pixel_height = FFI::CP437Console.get_console_pixel_height
    end


    # ---=== FONT MANAGEMENT : ===---
    def font
      FFI::CP437Console.get_current_font
    end

    def font=(font_name)
      FFI::CP437Console.set_gc_font font_name
      @pixel_width  = FFI::CP437Console.get_console_pixel_width
      @pixel_height = FFI::CP437Console.get_console_pixel_height
    end


    # ---=== MOUSE : ===---
    def mouse_coords(args)
      [ ( args.inputs.mouse.point.x / 8 ).to_i,
        ( ( 720 - args.inputs.mouse.point.y ) / 8 ).to_i ]
    end


    # ---=== GRAPHIC CONTEXT : ===---
    def current_glyph_index=(index)
      FFI::CP437Console.set_gc_index index
    end

    def current_foreground=(color)
      FFI::CP437Console.set_gc_foreground CP437::Color::pack_color(*color)
    end

    def current_background=(color)
      FFI::CP437Console.set_gc_background CP437::Color::pack_color(*color)
    end


    # ---=== DRAWING : ===---
    
    # --- Clearing :
    def clear
      FFI::CP437Console.clear_console()
    end

    # --- Single glyphs :
    def glyph_at(x,y)
      FFI::CP437Console.get_glyph_at(x,y)
    end

    def draw_glyph_at(x,y)
      FFI::CP437Console.draw_glyph_at x, y
    end

    # --- Strings :
    def draw_string_at(string,x,y)
      FFI::CP437Console.draw_string_at string, x, y
    end

    # --- Lines :
    def draw_horizontal_line(x1,x2,y)
      FFI::CP437Console.draw_horizontal_line x1, x2, y
    end

    def draw_vertical_line(x,y1,y2)
      FFI::CP437Console.draw_vertical_line x, y1, y2
    end

    def draw_line(x1,y1,x2,y2)
      FFI::CP437Console.draw_line x1, y1, x2, y2
    end

    def draw_antialiased_line(x1,y1,x2,y2)
      FFI::CP437Console.draw_antialiased_line x1, y1, x2, y2
    end

    # --- Rectangles :
    def stroke_rectangle(x,y,width,height)
      FFI::CP437Console.stroke_rectangle x, y, width, height
    end

    def fill_rectangle(x,y,width,height)
      FFI::CP437Console.fill_rectangle x, y, width, height
    end

    # --- Windows :
    def draw_window(x,y,width,height)
      FFI::CP437Console.draw_window x, y, width, height
    end

    def draw_thin_window(x,y,width,height)
      FFI::CP437Console.draw_thin_window x, y, width, height
    end

    def draw_thick_window(x,y,width,height)
      FFI::CP437Console.draw_thick_window x, y, width, height
    end
  end

  module Glyph
    def self.create(index,background,foreground)
      glyph             = FFI::CP437Console::Glyph.new
      glyph.index       = index 
      glyph.background  = CP437::Color::pack_color *background
      glyph.foreground  = CP437::Color::pack_color *foreground

      glyph
    end
  end

  module Color
    def self.pack_color(red,green,blue,alpha)
      (alpha<<24) | (blue<<16) | (green<<8) | red
    end

    def self.unpack_color(packed_color)
      red   = packed_color & 0xff
      green = ( packed_color & 0xff00 ) >> 8
      blue  = ( packed_color & 0xff0000 ) >> 16
      alpha = ( packed_color & 0xff000000) >> 24

      [ red, green, blue, alpha ]
    end
  end
end
