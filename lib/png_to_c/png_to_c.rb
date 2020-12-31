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

char_height.times do |char_y| do
  char_width.times do |char_x| do
    c_code += "{ "
    pixel_height.times do |pixel_y|
      line = 0
      pixel_width.times do |pixel_x|
        pixel_index =
        line |= image
      end

    end
  end
end

c_code += "};\n"
