require 'lib/cp437_console.rb'

RAND_SIZE       = 10000
RAND            = RAND_SIZE.times.map { |i| rand }
@rand_index     = rand RAND_SIZE





################################################################################
# 1. SETUP :
################################################################################
def setup(args)
  # --- Creating the console :
  args.state.font_index = 0   # keeping track of the current font

  # The console can be positioned anywhere in the DragonRuby window and it's ... 
  # ... size is not restricted to the window's size either. It can be bigger ...
  # ... or smaller. It can also be scalled by an integer factor.
  # The console can use several fonts. It's final size in pixels therefore   ...
  # ... depends on the font size, the console size in glyphs, and the        ...
  # ... scalling factor. All those parameters can be set or queried through  ...
  # ... appropriate methods. See the documentation.
  # At startup, the console is filled with the same single glyph, glyph      ...
  # color and background color passed as the 3 last arguments.
  #
  # For this first example, we'll setup a console that will fill the whole   ...
  # ... DragonRuby window. We chose an 8x8 font, so 160x90 glyphs with a     ...
  # ... scalling factor of 1 is 1280x720 pixels, exactly the DragonRuby's    ...
  # ... dimensions. We also chose a single point glyph (index 249 in the     ...
  # ... CP437 table) for the startup fill character so we can immediatly see ...
  # ... if our console was properly initialized.


  args.state.console    = CP437::Console.new  0, 0,               # the x and y position of the console
                                              160, 90,            # the width and height of the console (in glyphs)
                                              1,                  # the console's scaling factor
                                              CP437::FONT_LIST[args.state.font_index],  # the font
                                              249,                # the startup fill glyph index
                                              [64, 64, 64, 255],  # the startup fill glyph color
                                              [ 0,  0,  0, 255]   # the startup fill background color

  # --- Demos setup :
  args.state.current_demo     = :single_glyphs_and_strings

  args.state.antialiased      = false

  args.state.new_glyph_index  = randv * 255
  args.state.new_foreground   = [ 150 + randv * 105, 150 + randv * 105, 150 + randv * 105, 255 ]
  args.state.new_background   = [       randv * 100,       randv * 100,       randv * 100, 255 ]
  args.state.new_x            = ( 8 + randv * 72 ).to_i
  args.state.new_y            = ( 8 + randv * 37 ).to_i
  args.state.new_width        = ( randv * 72 ).to_i
  args.state.new_height       = ( randv * 37 ).to_i

  args.state.stroke_rectangle = true

  args.state.setup_done       = true
end





################################################################################
# 2. MAIN LOOP :
################################################################################
def tick(args)
  setup(args) unless args.state.setup_done

  case args.state.current_demo
  # --- 1. Drawing single glyphs and strings : #################################
  when :single_glyphs_and_strings
    args.state.single_glyph_done  = false
    unless  args.state.single_glyph_done then

      # To know what glyphs to draw, the console uses a graphic context that ...
      # ... has to be properly setup before any drawing operation is actually...
      # ... done.
      # The 3 most common operations are setting the drawing glyph, the      ...
      # ... drawing glyph color and the background color for the subsequent  ...
      # ... drawing calls.

      # WARNING!!!  WARNING!!! WARNING!!! WARNING!!! WARNING!!! WARNING!!!
      # None of the graphic methods check for out of console boundary access ...
      # If you try to write outside of the console you app WILL crash!!!
      # WARNING!!!  WARNING!!! WARNING!!! WARNING!!! WARNING!!! WARNING!!!

      # Before drawing anything, let's clear the console. The clear glyph,   ...
      # ... glyph color and background color are automatically set to the    ...
      # ... startup parameters. That can be changed at anytime through calls ...
      # ... to graphic context methods.
      args.state.console.clear

      # This example draws the complete fontset in a 16x16 grid, gradating   ...
      # ... the glyph and background colors.
      16.times do |i|
        16.times do |j|
          args.state.console.current_glyph_index  = j + 16 * i
          args.state.console.current_foreground   = [ 255 - 16 * i,      0,      0, 255 ]
          args.state.console.current_background   = [       16 * i, 16 * i, 16 * i, 255 ]
          args.state.console.draw_glyph_at 72 + j, 37 + i
        end
      end

      # Drawing strings is easy too. Set the glyph and background color and  ...
      # ... just draw the string at the wherever you want.
      args.state.console.current_foreground   = [ 255, 255, 255, 255 ]
      args.state.console.current_background   = [   0,   0,   0, 255 ]
      args.state.console.draw_string_at "- space : next sample -", 69, 10

      args.state.current_demo = :lines_and_mouse if args.inputs.keyboard.key_down.space
    end


  # --- 2. Drawing lines : #####################################################
  when :lines_and_mouse
    args.state.console.clear    # you know this one already
    
    # You can query the mouse position in the console coordinate system.
    mouse_x, mouse_y  = args.state.console.mouse_coords(args)

    args.state.console.current_glyph_index  = 1   # nice smile
    args.state.console.current_foreground   = [ 255, 0,   0, 255 ]
    args.state.console.current_background   = [   0, 0, 255, 255 ]
    if args.state.antialiased then
      args.state.console.draw_antialiased_line 80, 45, mouse_x, mouse_y
    else
      args.state.console.draw_line 80, 45, mouse_x, mouse_y
    end  

    # You know this one too.
    args.state.console.current_foreground   = [ 255, 255, 255, 255 ]
    args.state.console.current_background   = [   0,   0,   0, 255 ]
    args.state.console.draw_string_at "- a : toggle antialiasing -", 66, 7 
    args.state.console.draw_string_at "- space : next sample -",     69, 5

    args.state.antialiased  = !args.state.antialiased if args.inputs.keyboard.key_down.a
    args.state.current_demo = :rectangle_and_windows  if args.inputs.keyboard.key_down.space


  # --- 3. Drawing rectangles and windows : ####################################
  when :rectangle_and_windows
    args.state.console.clear

    # You can draw windows of different flavours. The thin and think window  ...
    # ... types are prebuilt. You can also define your own window style with ...
    # ... specific corner and side glyph indices. Colors are defined by the  ...
    # ... usual graphic context operations.

    # A thin window :
    args.state.console.draw_thin_window   0, 0, 160, 90
    args.state.console.draw_string_at     " a thin window ", 2, 89

    # A thick window :
    args.state.console.draw_thick_window  2, 2, 156, 86
    args.state.console.draw_string_at     " a thick window ", 4, 87

    # A custom window :
    args.state.console.window_top_left_index      = 244
    args.state.console.window_top_right_index     = 63
    args.state.console.window_bottom_left_index   = 168
    args.state.console.window_bottom_right_index  = 245
    args.state.console.window_left_right_index    = 240
    args.state.console.window_top_bottom_index    = 227
    args.state.console.draw_window    4, 4, 152, 82
    args.state.console.draw_string_at " a custom window ", 6, 85

    # You can also stroke and fill rectangles :
    if args.state.tick_count % 20 == 0 then
      args.state.new_glyph_index  = randv * 255
      args.state.new_foreground   = [ 150 + randv * 105, 150 + randv * 105, 150 + randv * 105, 255 ]
      args.state.new_background   = [       randv * 100,       randv * 100,       randv * 100, 255 ]

      args.state.new_x            = (  8 + randv * 72 ).to_i
      args.state.new_y            = (  8 + randv * 37 ).to_i
      args.state.new_width        = ( 10 + randv * 62 ).to_i
      args.state.new_height       = ( 10 + randv * 27 ).to_i
    end

    args.state.console.current_glyph_index  = args.state.new_glyph_index
    args.state.console.current_foreground   = args.state.new_foreground
    args.state.console.current_background   = args.state.new_background

    if args.state.stroke_rectangle then
      args.state.console.stroke_rectangle args.state.new_x,
                                          args.state.new_y,
                                          args.state.new_width,
                                          args.state.new_height
    else
      args.state.console.fill_rectangle args.state.new_x,
                                        args.state.new_y,
                                        args.state.new_width,
                                        args.state.new_height
    end

    args.state.console.current_foreground   = [ 255, 255, 255, 255 ]
    args.state.console.current_background   = [   0,   0,   0, 255 ]
    args.state.console.draw_string_at "- s : toggle stroke/fill -", 67, 8
    args.state.console.draw_string_at "- space : next sample -",     69, 6

    args.state.stroke_rectangle = !args.state.stroke_rectangle  if args.inputs.keyboard.key_down.s
    args.state.current_demo     = :polygons                     if args.inputs.keyboard.key_down.space

  when :polygons
    # You can also draw arbitrary polygons, same as rectangles.


  end

  #if args.inputs.keyboard.key_down.space then
  #  args.state.font_index   = ( args.state.font_index + 1 ) % FONT_LIST.length
  #  args.state.console.font = FONT_LIST[args.state.font_index]
  #end

  #if args.inputs.keyboard.key_down.plus then
  #  new_width   = args.state.console.width  + 1
  #  new_height  = args.state.console.height + 1
  #  args.state.console.resize new_width, new_height
  #end

  #if args.inputs.keyboard.key_down.hyphen then
  #  new_width   = args.state.console.width  - 1
  #  new_height  = args.state.console.height - 1
  #  args.state.console.resize new_width, new_height
  #end

  args.state.console.render(args)

  #args.outputs.labels << [ 20, 700, "mouse position: #{mouse_x},#{mouse_y} with glyph: #{glyph}.", 255, 255, 255, 255 ]
  #args.outputs.primitives << args.gtk.current_framerate_primitives
end

def randv
  @rand_index = (@rand_index + 1) % RAND_SIZE
  RAND[@rand_index]
end
