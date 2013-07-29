#! /usr/local/bin/ruby -Ku
# -*- coding: utf-8 -*-

$filename = "morph.txt"
$maxno = 10000
$maxline = 48
$limitlength = 4

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

def getwidechar(t, s, n)
  in_n = 0
  out_n = 0
  
  target = ""
  while in_n < n do
    if /[^ -~｡-ﾟ]/ =~ s[in_n] then
      target += s[in_n]
      out_n += 1
      in_n += 1
    else
      in_n += 1
    end
  end

  t.replace(target)


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

$oldLineGlobal = "私は人工無能です。"

def setstartch(startch, newline)

  target = ""
  line = ""
  count = 0
  $oldLineGlobal = "私は人工無能です。"
  if setrnd(3) < 2 then
    line = newline
  else
    line = $oldLineGlobal
  end
  
  getwidechar(target, line, line.length())
  


  last = typeset(target[0])
  for i in 0..target.length()
    now = typeset(target[i])
    if now != last then
      count += 1
      last = now
    end
    i += 1
  end
  startpoint = setrnd(count+1)

  count = 0
  i = 0
  last = typeset(target[0])
  for i in 0..target.length()
    now = typeset(target[i])
    if now != last then
      count += 1
      last = now
    end
    if count >= startpoint then
      break
    end
    i += 1
  end

  startch = ""
  for i in 0..target.length()
    now = typeset(target[i])
    if now!=last || ispunct(target[i]) then
      break
    end
    startch += target[i]
    j += 1
    i += 1
  end

  if startch.length() < $limitlength then
    startch = "人工知能"
    $oldLineGlobal = newline
  end
  
end

def addmorph(line)
  target = ""
  file = File.open($filename, "a")
  getwidechar(target, line, line.length())
  outputmorph(target,file)
  file.close
end


puts "さくら：メッセージをどうぞ"
print "あなた："

line = ""
db = Array.new($maxno){
  Array.new(2){""}}
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
