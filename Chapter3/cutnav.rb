# -*- coding: utf-8 -*-
def getsource(source)
  tmp = ""
  while l = STDIN.gets
    tmp += l.chomp
  end
  source.replace(tmp)
  return source.length
end

def getwidechar(source, n)
  target = ""
  for i in 0..n-1
    if /[^ -~｡-ﾟ]/ =~ source[i] then
      target += source[i]
    end
  end
  return target
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


def outputnoun(target)
  last = typeset(target[0])
  for l in 0..target.length()
    now = typeset(target[l])
    if now!=last && last==0 then
      puts ""
    end
    if now == 0 then
      print target[l]
    end
    last = now
  end
end

def outputp(target, str)
  last = typeset(target[0])
  k = ""
  if last == 0 then
    k += target[0]
  end
  for l in 1..target.length()
    now = typeset(target[l])
    if now == 0 then
      k += target[l]
    end
    if now!=last && last==0 then
      if target[l] == str[0] then
        puts k.to_s + str.to_s
      end
      k = ""
    end
    last = now
  end
end

source = ""
numchar = getsource(source)
target = getwidechar(source, numchar)


if ARGV.length()==0 then
  outputnoun(target)
elsif ARGV[0]=="n" then
  outputnoun(target)
elsif ARGV[0]=="v" then
  outputp(target,"う")
elsif ARGV[0]=="a" then
  outputp(target,"い")
elsif ARGV[0]=="d" then
  outputp(target,"た")
end

