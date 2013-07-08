# -*- coding: utf-8 -*-
$nMax = 8192
$nFile = "noun.txt"
$vFile = "verb.txt"
$aFile = "adj.txt"
$dFile = "adjv.txt"

$nlist = Array.new($nMax){ "" }
$nnum = 0
$vlist = Array.new($nMax){ "" }
$vnum = 0
$alist = Array.new($nMax){ "" }
$anum = 0
$dlist = Array.new($nMax){ "" }
$dnum = 0

def setrnd(num)
  return rand(num)
end

def vp()
  r = setrnd(3)
  case r
  when 2
    print $vlist[setrnd($vnum)]
  when 1
    print $alist[setrnd($anum)]
  when 0
    print $dlist[setrnd($dnum)]
  end
end

def ap()
  r = setrnd(2)
  case r
  when 1
    ap()
    print $alist[setrnd($anum)]
  when 0
    print $alist[setrnd($anum)]
  end
end  
  

def np()
  r = setrnd(2)
  case r
  when 1
    ap()
    print $nlist[setrnd($nnum)]
    print "は"
  when 0
    print $nlist[setrnd($nnum)]
    print "は"
    
  end
end

def sentence()
  np()
  vp()
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


$nnum = setlist($nlist, $nFile)
$vnum = setlist($vlist, $vFile)
$anum = setlist($alist, $aFile)
$dnum = setlist($dlist, $dFile)

for i in 0..50
  sentence()
  puts "。"
end

