require 'json'
require './raw_data.rb'

FACES = [ { vertices: [ 0, 1, 2, 3 ], color: :red     },
          { vertices: [ 3, 2, 6, 7 ], color: :green   },
          { vertices: [ 7, 6, 5, 4 ], color: :blue    },
          { vertices: [ 4, 5, 1, 0 ], color: :yellow  },
          { vertices: [ 3, 7, 4, 0 ], color: :orange  },
          { vertices: [ 1, 5, 6, 2 ], color: :purple  } ]

COLORS  = { red:    [ 255,   0,   0, 255 ],
            green:  [   0, 255,   0, 255 ],
            blue:   [   0,   0, 255, 255 ],
            yellow: [ 255, 255,   0, 255 ],
            orange: [ 255, 134,   0, 255 ],
            purple: [ 255,   0, 255, 255 ] }

def normal(u,v)
  [ u[1] * v[2] - u[2] * v[1],
    u[2] * v[0] - u[0] * v[2],
    u[0] * v[1] - u[1] * v[0] ]
end

def scale_projection(vertex, scale)
  [ 80 + ( ( vertex[0] - 640 ) / scale ).to_i,
    45 + ( ( vertex[1] - 360 ) / scale ).to_i ]
end

VERTICES_DATA.each.with_index do |frame,i|
  frame_data = []
  FACES.each.with_index do |face,j|
    vertex_1  = frame[face[:vertices][0]][:view]
    vertex_2  = frame[face[:vertices][1]][:view]
    vertex_3  = frame[face[:vertices][2]][:view]

    u = [ vertex_2[0] - vertex_1[0],
          vertex_2[1] - vertex_1[1],
          vertex_2[2] - vertex_1[2] ]
    v = [ vertex_3[0] - vertex_1[0],
          vertex_3[1] - vertex_1[1],
          vertex_3[2] - vertex_1[2] ]

    if normal(u, v)[2] < 0.0 then
      frame_data << { index: j, color: COLORS[face[:color]], vertices: face[:vertices].map {|i| scale_projection(frame[i][:projection], 2)} }
    end
  end
  puts JSON::dump frame_data
end
