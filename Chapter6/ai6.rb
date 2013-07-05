#! /usr/local/bin/ruby -Ku
# -*- coding: utf-8 -*-

$filename = "morph.txt"
$maxno = 10000
$maxline = 48

def readmorph(db)
  
  file = File.open($filename)
  
  l = file.gets
  oldline = l.chomp
  i = 0
  while l = file.gets do
    line = l.chomp

    db[i][0] = oldline
    db[i][1] = line
    oldline = line
    
    i += 1

    if i >= $maxno then
      puts "形態素の和を" + $maxno.to_s + "に制限します。"
      break
    end
  end

  file.close
  
  return i

end


def findch(startch, db, n)
  no = 0
  for i in 0..n-1
    if startch==db[i][0] then
      no += 1
    end
  end
  return no
end

def setrnd(num)
  return rand(num)
end

def setrndstr(startch, db, n)
  return db[setrnd(n)][1]
end


def setnext(startch, db, n, num)
  point = setrnd(num)
  no = -1
  for i in 0..n
    if startch==db[i][0] then
      no += 1
    end
    if no == point then
      return db[i][1]
      break
    end
  end
end


def generates(inputString, db2gram, n)
  startch = inputString.dup
  print startch
  begin
    num = findch(startch, db2gram, n)
    if num != 0 then
      startch = setnext(startch, db2gram, n, num)
    else
      startch = setrndstr(startch, db2gram, n)
    end
    print startch
  end while startch!='．' && startch!='，' && startch!='、' && startch!='。'
  puts ""
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

def ispunct(s)
  if s=="。" ||
      s=="、" ||
      s=="，" ||
      s=="．"  then
    return false
  else
    return true
  end
end

def getwidechar(source)
  target = ""
  for i in 0..source.length()-1
    if /[^ -~｡-ﾟ]/ =~ source[i] then
      target += source[i]
    end
  end
  return target
end

def outputmorph(target, file)
  i = 0
  last = typeset(target[i])
  while target[i]!="\0" && i<$maxline 
    if ispunct(target[i]) then
      now = typeset(target[i])
      if now != last then
        file.puts ""
        last = now
      end

      file.print target[i]
      i += 1
    else
      file.puts ""
      file.print target[i]
      i += 1
      file.puts ""
      last = typeset(target[i])
    end
  end
end

def setstartch(startch, line)
  rt = ""
  for i in 0..line.length()
    if iskanji(line[i]) then 
      break;
    end
  end
  
  if i == line.length() then
    rt = "人工知能"
  else
    j=0
    while iskanji(line[i]) && line[i]!="\0" do
      rt[j] = line[i]
      j += 1
      i += 1
    end
  end
  return rt
end

def addmorph(line)
  target = ""
  file = File.open($filename, "a")
  target = getwidechar(line)
  outputmorph(target,file)
  file.close
end


puts "さくら：メッセージをどうぞ"
print "あなた："

line = ""
db = Array.new($maxno){
  Array.new(2,"")}
startch = ""


while line = STDIN.gets
  addmorph(line.chomp)
  n = readmorph(db)
   print "さくら："
   startch = setstartch(startch,line)
   generates(startch,db,n)
   print "あなた："
end

puts "ばいばーい"
