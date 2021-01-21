require 'lib/cp437_console.rb'

RAND_SIZE       = 10000
RAND            = RAND_SIZE.times.map { |i| rand }
@rand_index     = rand RAND_SIZE

CONSOLE_WIDTH   = 40#160
CONSOLE_HEIGHT  = 22#90

FONT_LIST       = [ "cp437_8x8",
                    "cp437_8x14",
                    "cp437_8x16" ]

def setup(args)
  args.state.font_index = 0

  args.state.console    = CP437::Console.new  50, 50,
                                              3,
                                              CONSOLE_WIDTH,
                                              CONSOLE_HEIGHT,
                                              FONT_LIST[args.state.font_index],
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
  
  puts  "using font #{args.state.console.font.name.str} " \
        "of size #{args.state.console.font.width}x"       \
        "#{args.state.console.font.height}"

  16.times do |i|
    16.times do |j|
      args.state.console.current_glyph_index  = j + 16 * i
      args.state.console.draw_glyph_at j, i
    end
  end
  
  args.state.console.current_glyph_index  = 1
  args.state.console.current_foreground   = [ 255, 0, 0, 255 ]
  args.state.console.current_background   = [ 0, 0, 255, 255 ]
  vertices  = [ [10, 10], [12, 34], [50, 28], [45, 5] ]
  #args.state.console.fill_polygon vertices

  args.state.console.draw_string_at "banane !?!", 20, 10
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

  #args.state.console.clear

  #line_end = [ args.state.console.get_mouse_coords(args)[0]>>1,
  #             args.state.console.get_mouse_coords(args)[1]>>1 ]
  #args.state.console.draw_antialiased_line CONSOLE_WIDTH>>1, CONSOLE_HEIGHT>>1, line_end[0], line_end[1]

  if args.inputs.keyboard.key_down.space then
    args.state.font_index   = ( args.state.font_index + 1 ) % FONT_LIST.length
    args.state.console.font = FONT_LIST[args.state.font_index]
  end

  if args.inputs.keyboard.key_down.plus then
    new_width   = args.state.console.width  + 1
    new_height  = args.state.console.height + 1
    args.state.console.resize new_width, new_height
  end

  if args.inputs.keyboard.key_down.hyphen then
    new_width   = args.state.console.width  - 1
    new_height  = args.state.console.height - 1
    args.state.console.resize new_width, new_height
  end

  args.state.console.render(args)

  #args.outputs.primitives << args.gtk.current_framerate_primitives
  mouse_x, mouse_y  = args.state.console.mouse_coords(args)
  glyph             = args.state.console.glyph_at(mouse_x, mouse_y).index
  args.outputs.labels << [ 20, 700, "mouse position: #{mouse_x},#{mouse_y} with glyph: #{glyph}." ]
end

def randv
  @rand_index = (@rand_index + 1) % RAND_SIZE
  RAND[@rand_index]
end
