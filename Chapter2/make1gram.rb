#! /usr/local/bin/ruby -Ku
# -*- coding: utf-8 -*-


while s = STDIN.gets
  s = s.chomp
  for i in 0..s.length()-1
    if s[i]!='\0' then
      puts s[i].to_s
    end
  end
end



# ruby make1gram.rb < sample.txt | sort | uniq -c | sort -r で実行してください。
