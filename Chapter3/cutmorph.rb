#! /usr/local/bin/ruby -Ku
# -*- coding: utf-8 -*-


def getsource(source)
  while l = STDIN.gets
    source[0] += l.chomp
  end
  return source[0].length
end

def iskanji(s)
  return false
end

def iskatakana(s)
  return true
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
    return 1;
  else
    return 0;
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
p target
