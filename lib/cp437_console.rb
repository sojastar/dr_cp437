$gtk.ffi_misc.gtk_dlopen("cp437_console")

module CP437
  FONT_LIST = [ "cp437_8x8",
                "cp437_8x14",
                "cp437_8x16" ]

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

    B = Color::pack_color   0,   0,   0, 255
    W = Color::pack_color 255, 255, 255, 255
    R = Color::pack_color 255,   0,   0, 255
    G = Color::pack_color   0, 255,   0, 255
    B = Color::pack_color   0,   0, 255, 255
  end

  class Console
    attr_accessor :x, :y,
                  :scale
    attr_reader   :width, :height,
                  :pixel_width, :pixel_height,
                  :font_width, :font_height


    # ---=== INITIALIZATION : ===---
    def initialize(x,y,width,height,scale,font,index,foreground,background)
      init_glyph            = FFI::CP437Console::Glyph.new
      init_glyph.index      = index 
      init_glyph.foreground = CP437::Color::pack_color *foreground
      init_glyph.background = CP437::Color::pack_color *background

      @c_console            = FFI::CP437Console::init_console width, height, font, init_glyph

      @x, @y, @scale        = x, y, scale

      @width                = width
      @height               = height

      @pixel_width          = FFI::CP437Console.get_console_pixel_width(@c_console)
      @pixel_height         = FFI::CP437Console.get_console_pixel_height(@c_console)

      @font_width           = FFI::CP437Console.get_current_font(@c_console).width
      @font_height          = FFI::CP437Console.get_current_font(@c_console).height

      @vertices             = FFI::CP437Console.get_polygon_vertices_array(@c_console)

      @sprite_list          = {}
    end


    # ---=== RENDERING : ===---
    def render(args)
      FFI::CP437Console::update_console(@c_console)

      args.outputs.primitives << [@x,
                                  @y,
                                  @scale * @pixel_width,
                                  @scale * @pixel_height,
                                  :console].sprite
    end


    # ---=== GEOMETRY MANAGEMENT : ===---
    def resize(width,height)
      FFI::CP437Console.resize_console(@c_console, width, height)
      @width        = width
      @height       = height
      @pixel_width  = FFI::CP437Console.get_console_pixel_width(@c_console)
      @pixel_height = FFI::CP437Console.get_console_pixel_heigh(@c_console)
    end


    # ---=== FONT MANAGEMENT : ===---
    def font
      FFI::CP437Console.get_current_font(@c_console)
    end

    def font=(font_name)
      FFI::CP437Console.set_gc_font font_name
      @pixel_width  = FFI::CP437Console.get_console_pixel_width(@c_console)
      @pixel_height = FFI::CP437Console.get_console_pixel_height(@c_console)
      @font_width   = FFI::CP437Console.get_current_font(@c_console).width
      @font_height  = FFI::CP437Console.get_current_font(@c_console).height
    end


    # ---=== MOUSE : ===---
    def mouse_coords(args)
      [ ( ( args.inputs.mouse.point.x - @x ) / ( @scale * @font_width ) ).to_i,
        ( ( args.inputs.mouse.point.y - @y ) / ( @scale * @font_height ) ).to_i ]
    end


    # ---=== GRAPHIC CONTEXT : ===---
    def current_glyph_index=(index)
      FFI::CP437Console.set_gc_index(@c_console, index)
    end

    def current_foreground=(color)
      FFI::CP437Console.set_gc_foreground(@c_console, CP437::Color::pack_color(*color))
    end

    def current_background=(color)
      FFI::CP437Console.set_gc_background(@c_console, CP437::Color::pack_color(*color))
    end

    def current_clear_glyph_index=(index)
      FFI::CP437Console.set_gc_clear_index(@c_console, index)
    end

    def current_clear_foreground=(color)
      FFI::CP437Console.set_gc_clear_foreground(@c_console, CP437::Color::pack_color(*color))
    end

    def current_clear_background=(color)
      FFI::CP437Console.set_gc_clear_background(@c_console, CP437::Color::pack_color(*color))
    end

    def window_top_left_index=(index)
      FFI::CP437Console.set_gc_window_top_left_index(@c_console, index)
    end

    def window_top_right_index=(index)
      FFI::CP437Console.set_gc_window_top_right_index(@c_console, index)
    end

    def window_bottom_left_index=(index)
      FFI::CP437Console.set_gc_window_bottom_left_index(@c_console, index)
    end

    def window_bottom_right_index=(index)
      FFI::CP437Console.set_gc_window_bottom_right_index(@c_console, index)
    end

    def window_top_bottom_index=(index)
      FFI::CP437Console.set_gc_window_top_bottom_index(@c_console, index)
    end

    def window_left_right_index=(index)
      FFI::CP437Console.set_gc_window_left_right_index(@c_console, index)
    end


    # ---=== DRAWING : ===---
    
    # --- Clearing :
    def clear
      FFI::CP437Console.clear_console(@c_console)
    end

    # --- Single glyphs :
    def glyph_at(x,y)
      FFI::CP437Console.get_glyph_at(@c_console, x, y)
    end

    def draw_glyph_at(x,y)
      FFI::CP437Console.draw_glyph_at(@c_console, x, y)
    end

    # --- Strings :
    def draw_string_at(string,x,y)
      FFI::CP437Console.draw_string_at(@c_console, string, x, y)
    end

    # --- Lines :
    def draw_horizontal_line(x1,x2,y)
      FFI::CP437Console.draw_horizontal_line(@c_console, x1, x2, y)
    end

    def draw_vertical_line(x,y1,y2)
      FFI::CP437Console.draw_vertical_line(@c_console, x, y1, y2)
    end

    def draw_line(x1,y1,x2,y2)
      FFI::CP437Console.draw_line(@c_console, x1, y1, x2, y2)
    end

    def draw_antialiased_line(x1,y1,x2,y2)
      FFI::CP437Console.draw_antialiased_line(@c_console, x1, y1, x2, y2)
    end

    # --- Rectangles :
    def stroke_rectangle(x,y,width,height)
      FFI::CP437Console.stroke_rectangle(@c_console, x, y, width, height)
    end

    def fill_rectangle(x,y,width,height)
      FFI::CP437Console.fill_rectangle(@c_console, x, y, width, height)
    end

    # --- Windows :
    def draw_window(x,y,width,height)
      FFI::CP437Console.draw_window(@c_console, x, y, width, height)
    end

    def draw_thin_window(x,y,width,height)
      FFI::CP437Console.draw_thin_window(@c_console, x, y, width, height)
    end

    def draw_thick_window(x,y,width,height)
      FFI::CP437Console.draw_thick_window(@c_console, x, y, width, height)
    end

    def stroke_polygon(vertices)
      vertices.each_cons(2) { |pair| FFI::CP437Console.draw_line(@c_console, *(pair.flatten)) }
      FFI::CP437Console.draw_line(@c_console, *(vertices.last + vertices.first).flatten)
    end

    def stroke_antialiased_polygon(vertices)
      vertices.each_cons(2) { |pair| FFI::CP437Console.draw_line(@c_console, *(pair.flatten)) }
      FFI::CP437Console.draw_antialiased_line(@c_console, *(vertices.last + vertices.first).flatten)
    end

    def fill_polygon(vertices)
      FFI::CP437Console.set_polygon_vertex_count(@c_console, vertices.length)
      vertices.length.times do |i|
        @vertices[2*i]    = vertices[i][0]
        @vertices[2*i+1]  = vertices[i][1]
      end
      FFI::CP437Console.fill_polygon(@c_console)
    end

    def draw_sprite_at(tag,x,y)
      FFI::CP437Console::draw_sprite_at(@c_console, @sprite_list[tag][:index], x, y)
    end

    def register_sprite(tag,width,height,glyphs)
      new_sprite          = FFI::CP437Console::create_sprite(@c_console, width, height)

      (width * height).times do |i|
        new_sprite.indices[i]     = glyphs[i][0]
        new_sprite.foregrounds[i] = glyphs[i][1]
        new_sprite.backgrounds[i] = glyphs[i][2]
      end

      @sprite_list[tag] = { index:  FFI::CP437Console::get_sprite_count(@c_console) - 1,
                            sprite: new_sprite }
    end
  end
end
