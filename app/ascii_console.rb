$gtk.ffi_misc.gtk_dlopen("ascii_console")

module ASCII
  class Console
    def initialize(width,height,index,background,foreground)
      init_glyph            = FFI::ASCIIConsole::Glyph.new
      init_glyph.index      = index 
      init_glyph.background = ASCII::Color::pack_color *background
      init_glyph.foreground = ASCII::Color::pack_color *foreground

      FFI::ASCIIConsole::init_console width, height, init_glyph

      @pixel_width  = FFI::ASCIIConsole.get_console_pixel_width
      @pixel_height = FFI::ASCIIConsole.get_console_pixel_height
    end

    def width()           FFI::ASCIIConsole.get_console_width   end
    def height()          FFI::ASCIIConsole.get_console_height  end
    def get_glyph_at(x,y) FFI::ASCIIConsole.get_glyph_at(x,y)   end

    def update
      FFI::ASCIIConsole::update_console
    end

    def render(args,x,y,scale)
      args.outputs.primitives << [100, 100, scale * @pixel_width, scale * @pixel_height, :console].sprite
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
