require 'app/cp437_console.rb'

RAND_SIZE       = 10000
RAND            = RAND_SIZE.times.map { |i| rand }
@rand_index     = rand RAND_SIZE

CONSOLE_WIDTH   = 160
CONSOLE_HEIGHT  = 90

def setup(args)
  args.state.console    = CP437::Console.new  CONSOLE_WIDTH,
                                              CONSOLE_HEIGHT,
                                              33,
                                              [0, 0, 255, 255],
                                              [255, 0, 0, 255]

  args.state.setup_done = true
end

def tick(args)
  setup(args) unless args.state.setup_done

  new_x     = rand CONSOLE_WIDTH
  new_y     = rand CONSOLE_HEIGHT
  new_glyph = CP437::Glyph::create  35,
                                    [randv, randv, randv, 255],
                                    [randv, randv, randv, 255]
  args.state.console.draw_glyph_at new_glyph, new_x, new_y

  args.state.console.update

  args.state.console.render(args, 0, 0, 1)

  args.outputs.primitives << args.gtk.current_framerate_primitives
end

def randv
  @rand_index = (@rand_index + 1) % RAND_SIZE
  RAND[@rand_index]
end
