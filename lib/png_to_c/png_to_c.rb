require 'chunky_png'
require 'optparse'


# ---=== PARSING OPTIONS : ===---
options = {}
OptionParser.new do |opts|
  opts.banner = "Usage: png_to_c.rb [options] file.png"

  opts.on("-pPIXEL_SIZE", "--pixel-size=PIXEL_SIZE", "width and height in pixels (WxH)") do |ps|
    options[:pixel_size] = ps
  end

  opts.on("-cCHAR_SIZE", "--char-size=CHAR_SIZE", "width and height in characters (WxH)") do |cs|
    options[:char_size] = cs
  end

  opts.on("-oOUTPUT", "--output=OUTPUT", "output base filename") do |o|
    options[:output] = o
  end
end.parse!

pixel_width,  pixel_height  = options[:pixel_size].split('x').map { |d| d.to_i }
char_width,   char_height   = options[:char_size].split('x').map { |d| d.to_i }
output                      = options[:output]
input                       = ARGV.last



# ---=== CONVERTING : ===---
image   = ChunkyPNG::Image.from_file input
c_code  = "unsigned char #{output}[256][8] = {\n"

char_height.times do |char_y|
  y_pixel_offset = char_y * pixel_height
  char_width.times do |char_x|
    x_pixel_offset = char_x * pixel_width
    c_code += "  { "
    pixel_height.times do |pixel_y|
      line = 0
      pixel_width.times do |pixel_x|
        pixel_index = ( y_pixel_offset + pixel_y ) * pixel_width * char_width + x_pixel_offset + pixel_x
        line |= image.pixels[pixel_index] > 255 ? (1 << pixel_x) : 0
      end
      c_code += "0x#{"%02X" % line}"
      c_code += ',' if pixel_y < pixel_height - 1
    end
    if char_x == char_width - 1 && char_y == char_height - 1 then
      c_code += " }\n" 
    else
      c_code += " },\n" 
    end
  end
end

c_code += "};\n"

File.open( output + '.h', 'w+' ) do |file|
  file.write c_code
end
