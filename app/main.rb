require 'app/ascii_console.rb'

def setup(args)
  args.state.console    = ASCII::Console.new  2, 2, 33, [255, 128, 63, 255], [0, 63, 128, 255]

  args.state.setup_done = true
end

def tick(args)
  setup(args) unless args.state.setup_done

  args.outputs.labels << [ 20, 700, "console width:  #{args.state.console.width}" ]
  args.outputs.labels << [ 20, 680, "console height: #{args.state.console.height}" ]

  first_glyph             = args.state.console.get_glyph_at(0,0)
  first_glyph_index       = first_glyph.index
  first_glyph_background  = ASCII::Color::unpack_color first_glyph.background
  first_glyph_foreground  = ASCII::Color::unpack_color first_glyph.foreground 
  args.outputs.labels << [ 20, 660, "glyph(0,0) index: #{first_glyph_index}, background: #{first_glyph_background}, foreground: #{first_glyph_foreground}" ]

  args.state.console.update

  args.outputs.background_color = [64, 0, 128]
  args.state.console.render(args, 100, 100, 1)
end
