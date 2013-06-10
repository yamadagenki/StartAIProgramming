#! /usr/local/bin/ruby -Ku
# -*- coding: utf-8 -*-


while s = STDIN.gets
  s = s.chomp
  for i in 0..s.length()-1
    if s[i]!='\0' && s[i+1]!='\0' && s[i+2]!='\0' then
      puts s[i].to_s + s[i+1].to_s + s[i+2].to_s
    end
  end
end


# ruby make3gram.rb < sample.txt | sort | uniq -c | sort -r で実行してください。



