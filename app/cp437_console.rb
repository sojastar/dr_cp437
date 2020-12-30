$gtk.ffi_misc.gtk_dlopen("cp437_console")

module CP437
  class Console
    def initialize(width,height,index,background,foreground)
      init_glyph            = FFI::CP437Console::Glyph.new
      init_glyph.index      = index 
      init_glyph.background = CP437::Color::pack_color *background
      init_glyph.foreground = CP437::Color::pack_color *foreground

      FFI::CP437Console::init_console width, height, init_glyph

      @pixel_width  = FFI::CP437Console.get_console_pixel_width
      @pixel_height = FFI::CP437Console.get_console_pixel_height
    end

    def width()           FFI::CP437Console.get_console_width   end
    def height()          FFI::CP437Console.get_console_height  end
    def get_glyph_at(x,y) FFI::CP437Console.get_glyph_at(x,y)   end

    def update
      FFI::CP437Console::update_console
    end

    def draw_glyph_at(glyph,x,y)
      FFI::CP437Console.draw_glyph_at glyph, x, y
    end

    def render(args,x,y,scale)
      args.outputs.primitives << [x, y, scale * @pixel_width, scale * @pixel_height, :console].sprite
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
