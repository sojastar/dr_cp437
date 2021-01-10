require 'app/cp437_console.rb'

RAND_SIZE       = 10000
RAND            = RAND_SIZE.times.map { |i| rand }
@rand_index     = rand RAND_SIZE

CONSOLE_WIDTH   = 160
CONSOLE_HEIGHT  = 90

def setup(args)
  args.state.console    = CP437::Console.new  CONSOLE_WIDTH,
                                              CONSOLE_HEIGHT,
                                              250,  # nice smile
                                              [0, 0, 0, 255],
                                              [64, 64, 64, 255]

  # Test lines :
  #args.state.console.set_current_glyph_index  176
  #args.state.console.set_current_background   [ 255, 255, 0, 255 ]
  #args.state.console.set_current_foreground   [   0, 255, 0, 255 ]
  #args.state.console.draw_horizontal_line     10, 150, 45
  #args.state.console.draw_vertical_line       80, 10, 80
  #args.state.console.draw_antialiased_line    10, 10, 150, 80

  # Test rectangles :
  #args.state.console.set_current_glyph_index  15
  #args.state.console.set_current_background   [ 0, 127, 255, 255 ]
  #args.state.console.set_current_foreground   [ 0, 255, 0, 255 ]
  #args.state.console.draw_window               1,  1, 12, 8
  #args.state.console.draw_thin_window         14,  1, 12, 8
  #args.state.console.draw_thick_window         1, 10, 12, 8
  
  args.state.console.set_current_background [ 0, 0, 0, 255 ]
  args.state.console.set_current_foreground [ 255, 255, 255, 255 ]

  args.state.setup_done = true
end

def tick(args)
  setup(args) unless args.state.setup_done

  #args.state.console.set_current_glyph_index  [ 3, 4, 5, 6 ].sample
  #args.state.console.set_current_background   [ randv, randv, randv, 255 ]
  #args.state.console.set_current_foreground   [ randv, randv, randv, 255 ]
  #new_x     = rand CONSOLE_WIDTH
  #new_y     = rand CONSOLE_HEIGHT
  #args.state.console.draw_glyph_at new_x, new_y

  args.state.console.clear_console

  line_end = args.state.console.get_mouse_coords(args)
  args.state.console.draw_antialiased_line 80, 45, line_end[0], line_end[1]

  args.state.console.update

  args.state.console.render(args, 0, 0, 1)

  #args.outputs.primitives << args.gtk.current_framerate_primitives
end

def randv
  @rand_index = (@rand_index + 1) % RAND_SIZE
  RAND[@rand_index]
end
