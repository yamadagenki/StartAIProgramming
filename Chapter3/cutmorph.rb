#! /usr/local/bin/ruby -Ku
# -*- coding: utf-8 -*-


def getsource(source)
  while l = STDIN.gets
    source[0] += l.chomp
  end
  return source[0].length
end

def iskanji(s)
  if /(?:\p{Hiragana}^|\p{Katakana}^|[一-龠々])/ =~ s then
    return true
  end
  return false
end

def iskatakana(s)
  if /(?:\p{Hiragana}^|\p{Katakana}|[一-龠々]^)/ =~ s then
    return true
  end
  return false
end

def typeset(s)
  if iskanji(s) then return 0
  elsif iskatakana(s) then return 1
  else return 2
  end
end

def isputct(s)
  if s=="。" ||
      s=="、" ||
      s=="，" ||
      s=="．"  then
    return false
  else
    return true
  end
end

def outputmorph(s)
  i = 0
  last = typeset(s[i])
  for l in 0..s.length()
    if isputct(s[i]) then
      now = typeset(s[i])
      if now != last then
        puts ""
        last = now
      end
      print s[i]
      i+=1
    else
      puts ""
      i+=1
      last = typeset(s[i])
    end
  end
end

def getwidechar(source, n)
  target = Array.new(1,"")
  for i in 0..n-1
    if /[^ -~｡-ﾟ]/ =~ source[0][i] then
      target[0] += source[0][i]
    end
  end
  return target[0]
end


source = Array.new(1,"")
numchar = getsource(source)
target = getwidechar(source, numchar)
outputmorph(target)
