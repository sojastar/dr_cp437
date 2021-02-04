# dr_cp437
A CP437 console for DragonRuby

![dr_cp437_demo](/demo.gif)

## Creating a console object:

```ruby
args.state.console    = CP437::Console.new  0, 0,               # the x and y position of the console
                                            160, 90,            # the width and height of the console (in glyphs)
                                            1,                  # the console's scaling factor
                                            CP437::FONT_LIST[args.state.font_index],  # the font
                                            249,                # the startup fill glyph index
                                            [64, 64, 64, 255],  # the startup fill glyph color in rgba format
                                            [ 0,  0,  0, 255]   # the startup fill background color in rgba format
 ```
 
At startup, the console is filled with the same single glyph, glyph color and background color. These are the last 3 arguments of the creator method.


## Drawing a single glyph:
 
 ```ruby
args.state.console.current_glyph_index  = 1                       # glyph == nice smiley!
args.state.console.current_foreground   = [ 255, 0,   0, 255 ]    # glyph color in rgba format
args.state.console.current_background   = [   0, 0, 255, 255 ]    # background color in rgba format
args.state.console.draw_glyph_at 12, 34                           # actually drawing the glyph
```

To know what glyph to draw, the console uses a graphic context that has to be properly setup before any drawing operation is actually done. The 3 most common operations are setting the drawing glyph, the drawing glyph color and the background color for all subsequent drawing calls.


 ## Clearing the console:
 
 ```ruby
 args.state.console.current_clear_glyph_index   = 255
 args.state.console.current_clear_foreground    = [ 64, 64, 64, 255 ]
 args.state.console.current_clear_background    = [  0,  0,  0, 255 ]
 args.state.console.clear
 ```
 
The clear glyph, glyph color and background color are automatically set to the startup fill parameters but can be modified by setting the `current_clear_glyph_index`, `current_clear_foreground` and `current_clear_background` attributes.


## Drawing a text string:

```ruby
args.state.console.draw_string_at 'A Beautiful String...', 10, 20
```

## Drawing lines :

There are two types of lines: normal and antialiased.

```ruby
args.state.console.draw_line 10, 20, 30, 40
```
or
```ruby
args.state.console.draw_antialiased_line 10, 20, 30, 40
```

When drawing normal lines, the glyph index, glyph color and background color currently set in the graphic context are used. When drawing an antialiased line, only the colors set in the graphic context are used. The antialiasing algorithm will chose glyphs that will give the impression of a seemingly straight line.


## Drawing rectangles:

```ruby
args.state.console.stroke_rectangle 10, 10, 40, 40
```
or
```ruby
args.state.console.fill_rectangle 10, 10, 40, 40
```

The glyph index, glyph color and background color are set with the usual graphic context methods.


## Drawing windows:

```ruby
args.state.console.draw_thin_window   10, 10, 40, 40
```
or
```ruby
args.state.console.draw_thick_window   10, 10, 40, 40
```
or
```ruby
args.state.console.window_top_left_index      = 244
args.state.console.window_top_right_index     = 63
args.state.console.window_bottom_left_index   = 168
args.state.console.window_bottom_right_index  = 245
args.state.console.window_left_right_index    = 240
args.state.console.window_top_bottom_index    = 227
args.state.console.draw_window   10, 10, 40, 40
```

There are 3 flavors of windows: thin border, thick border and custom. The glyph color and background color are set with the usual graphic context methods.


## Drawing polygons:

```ruby
args.state.console.stroke_polygon [ [ 10, 10 ], [ 20, 20 ], [ 30, 10 ] ]
```
or
```ruby
args.state.console.stroke_antialiased_polygon [ [ 10, 10 ], [ 20, 20 ], [ 30, 10 ] ]
```
or
```ruby
args.state.console.fill_polygon [ [ 10, 10 ], [ 20, 20 ], [ 30, 10 ] ]
```

The maximum vertex count for a polygon is 64.

## Drawing sprites:

Sprites are rectangular groups of glyphs that can be drawn anywhere in the console. Sprites have to be registered before they can be drawn. A sprite requires a registration tag (used as a reference for the drawing method draw_sprite_at), a width, a height, and lastly some glyph data matching the width and height and properly formated :
  [ [ index_1, foreground_1, background_1 ], ...
  [ index_n, foreground_n, background_n ] ] where n = width * height.
* index is the glyph index in the font
* foreground is the glyph color, properly formated by the CP437::Color::pack_color method.
* background is the background color, formated by the same method

```ruby
r = CP437::Color::pack_color  255,   0,   0, 255  # red
w = CP437::Color::pack_color  255, 255, 255, 255  # white
b = CP437::Color::pack_color    0,   0,   0, 255  # black

args.state.console.register_sprite  :my_beautiful_sprite,         # sprite tag
                                    2, 2,                         # sprite width and height
                                    [ [ 1, r, b ], [ 1, w, b ],   # a 2x2 red and white checker   ...
                                      [ 1, w, b ], [ 1, r, b ] ]  # ... pattern with smileys on a ...
                                                                  # ... black background
```

Glyphs with index 0 are considered transparent and will not be drawn.


## Mouse:

You can query the mouse position in the console coordinate system.
```ruby
mouse_x, mouse_y  = args.state.console.mouse_coords(args)
```
