require 'app/ascii_console.rb'
#$gtk.ffi_misc.gtk_dlopen("ascii_console")
#include FFI::ASCIIConsole

def setup(args)
  init_glyph            = ASCIIConsole::Glyph.new
  init_glyph.index      = 33
  init_glyph.background = ASCIIConsole::pack_color 255, 128, 63, 255
  init_glyph.foreground = ASCIIConsole::pack_color 0, 63, 128, 255
  FFI::ASCIIConsole::init_console 2, 2, init_glyph

  args.state.setup_done = true
end

def tick(args)
  setup(args) unless args.state.setup_done

  args.outputs.labels << [ 20, 700, "console width:  #{FFI::ASCIIConsole::get_console_width}" ]
  args.outputs.labels << [ 20, 680, "console height: #{FFI::ASCIIConsole::get_console_height}" ]

  first_glyph             = FFI::ASCIIConsole::get_glyph_at(0,0)
  first_glyph_index       = first_glyph.index
  first_glyph_background  = ASCIIConsole::unpack_color first_glyph.background
  first_glyph_foreground  = ASCIIConsole::unpack_color first_glyph.foreground 
  args.outputs.labels << [ 20, 660, "glyph(0,0) index: #{first_glyph_index}, background: #{first_glyph_background}, foreground: #{first_glyph_foreground}" ]

  FFI::ASCIIConsole::update_console
  args.outputs.background_color = [64, 0, 128]
  args.outputs.primitives << [100, 100, 4 * 8, 4 * 8, :console].sprite
end
