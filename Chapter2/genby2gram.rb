#! /usr/local/bin/ruby -Ku
# -*- coding: utf-8 -*-

def read2gram(db2gram)
  i = 0
  open("2gram.txt") {|file|
    while l = file.gets
      db2gram[i] = l.chomp
      i += 1
    end

  }

  return i 
end



def findch(startch, db2gram, n)
  no = 0
  for i in 0..n-1
    if startch==db2gram[i][0] then

      no += 1
    end
  end
  return no
end

def setrnd(num)
  return rand(num)
end



def setrndstr(startch, db2gram, n)
  point = setrnd(n)
  for i in 0..n-1
    if i==point then
      startch[0] = db2gram[i][1]
    end
  end
end



def setnext(startch, db2gram, n, num)
  point = setrnd(num)+1
  no = 0
  for i in 0..n
    if startch==db2gram[i][0] then
      no += 1
    end
    if no == point then
      startch[0] = db2gram[i][1]
      break
    end
  end
end



def generates(inputString, db2gram, n)
  startch = inputString.dup
  print startch[0]
  begin
    num = findch(startch, db2gram, n)
    if num != 0 then
      setnext(startch, db2gram, n, num)
    else
      setrndstr(startch, db2gram, n)
    end
   print startch[0]
 end while startch[0]!='．' && startch[0]!='，'
  puts ""
end


#main function
MAXNO = 100000
MAXLINE = 256

db2gram = Array.new(MAXNO, '\0')

num = read2gram(db2gram)

puts "開始文字を入力してください。"
inputString = STDIN.gets 
inputString = inputString.chomp

for i in 0..10
  generates(inputString, db2gram, num)
end

