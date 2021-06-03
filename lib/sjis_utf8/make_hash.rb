utf8_to_jp_font = {}

File.open('./ShiftJIS-UTF8.txt', 'r') do |tables|
  index = 0
  tables.each_line do |line|
    columns = line.split

    unless columns.first == "区" then
      if columns[5] != '------' then 
        utf8                  = columns[5].chars.each_slice(2).map { |b| b.join.to_i(16) }
        utf8_to_jp_font[utf8] = index
      end

      index += 1
    end

  end
end

File.open('./utf8_to_jp_font.rb', 'w+') do |source|
  source.write "module CP437\n  UTF8_TO_JP_FONT = {\n"
  utf8_to_jp_font.each_pair do |utf8,index|
    source.write "    #{utf8} => #{index},\n"
  end
  source.write "  }\nend"
end
