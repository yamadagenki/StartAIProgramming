# -*- coding: utf-8 -*-
$poolSize = 30
$ruleSize = 4
$locusSize = 4

$gMax = 10000
$mutationRate = 0.1

$lowerLimit = 0
$maxLines = 64
$lineSize = 64


def setrnd(num)
  return rand(num)
end


def initgen(gene)
  for i in 0..$poolSize
    for j in 0..$ruleSize
      for k in 0..$locusSize
        gene[i][j][k] = "A" + setrnd(26)
      end
    end
  end
end

    
def score(singlerule, lines, lineno)
  score = 0
  for l in 0..lineno
    localscore = 0
    for i in 0..$locusSize 
      if lines[l].index(singlerule[i])!=nil then
        localscore += 1
      end
      if localscore >= $locusSize then
        score += 1
      end
    end
  end
  return score
end

def fitness(sgene, lines, lineno)
  fvalue = 0
  for j in 0..$ruleSize
    fvalue += score(sgene[j], lines, lineno)
  end
  return fvalue
end


def printgene(gene, lines, lineno)
  for i in 0..$poolSize
    fvalue = fitness(gene[i], lines, lineno)
    if fvalue >= $lowerLimit then
      print i.to_s + " : "
      for j in i..$ruleSize
        for k in k..$locusSize
          print gene[i][j][k]
          if j < $ruleSize-1 then
            print ", "
          end
        end
      end
      print "\t"
      puts fvalue.to_s
    end
  end
end

def fave(gene, lines, lineno)
  fsum = 0.0
  
  for i in 0..$poolSize
    fsum += fitness(gene[i],lines,lineno)
  end
  return fsum / $poolSize
end

def readlines(lines)
  n = 0

  while l = STDIN.gets
    lines[n] = l.chomp
    n += 1
    if n >= $maxLines then
      n -= 1
      puts "警告 行数を" + n.to_s + "に制限しました\n"
      break
    end
    if lines[n-1].length() <= 2 then
      n -= 1
      break
    end
  end
  return n
end


def mutation(gene)
  for i in 0..$poolSize
    for j in 0..$ruleSize
      for k in 0..$locusSize
        gene[i][j][k] = "A" + setrnd(26)
      end
    end
  end
end


gene = Array.new($poolSize){
  Array.new($ruleSize){
    Array.new($locusSize, "")
  }
}

lines = Array.new($maxlines){
    Array.new($lineSize, "")
}

lineno = readlines(lines)
initgene(gene)
for generation in 0..$gMax
  puts "第" + generation.to_s + "世代平均適応度\t" + fave(gene, lines, lineno).to_s
  printgene(gene, lines, lineno)
  mutation(gene)
end
