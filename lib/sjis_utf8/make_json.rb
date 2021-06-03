utf8_to_jp_font = {}

File.open('./ShiftJIS-UTF8.txt', 'r') do |tables|
  index       = 0
  first_bytes = [[], [], []]

  tables.each_line do |line|
    columns = line.split

    unless columns.first == "区" then
      if columns[5] != '------' then 
        utf8_to_jp_font[columns[5]] = index
        case columns[5].length
        when 2 then first_bytes[0] << columns[5][0,2] 
        when 4 then first_bytes[1] << columns[5][0,2]
        when 6 then first_bytes[2] << columns[5][0,2]
        end
      end

      index += 1
    end
  end

  first_bytes[0].uniq!
  first_bytes[1].uniq!
  first_bytes[2].uniq!

  puts '-'
  puts first_bytes[0]
  puts '--'
  puts first_bytes[1]
  puts '---'
  puts first_bytes[2]
end

#File.open('./utf8_to_jp_font.json', 'w+') do |source|
#  source.write "{\n"
#  utf8_to_jp_font.each_pair do |utf8,index|
#    source.write "  \"#{utf8}\" : #{index},\n"
#  end
#  source.write "}\n"
#end
