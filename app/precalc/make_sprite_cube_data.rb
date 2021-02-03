require 'json'
require './raw_data.rb'

def scale_projection(vertex, scale)
  [ 80 + ( ( vertex[0] - 640 ) / scale ).to_i,
    45 + ( ( vertex[1] - 360 ) / scale ).to_i ]
end

VERTICES_DATA.each.with_index do |frame|
  frame_data = frame.sort_by { |vertex| vertex[:view][2] }.map { |vertex| scale_projection(vertex[:projection], 2) }
  puts JSON::dump frame_data
end
