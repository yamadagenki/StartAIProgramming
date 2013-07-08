# -*- coding: utf-8 -*-
$nMax = 8192
$nFile = "noun.txt"
$vFile = "verb.txt"

def setrnd(num)
  return rand(num)
end

def vp(vlist, vnum)
  print vlist[setrnd(vnum)]
end


def np(nlist, nnum)
  print nlist[setrnd(nnum)]
  print "は"
end

def sentence(nlist, nnum, vlist, vnum)
  np(nlist,nnum)
  vp(vlist,vnum)
end

def setlist(list, filename)

  fp = File.open(filename)
  i = 0
  while l = fp.gets
    list[i] = l.chomp
    i += 1
  end
  fp.close
  return i
end

nlist = Array.new($nMax){ "" }
vlist = Array.new($nMax){ "" }

nnum = setlist(nlist, $nFile)
vnum = setlist(vlist, $vFile)

for i in 0..50
  sentence(nlist, nnum, vlist, vnum)
  puts "。"
end

