# -*- coding: utf-8 -*-
$poolSize = 30
$ruleSize = 4
$locusSize = 4

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


def initgene(gene)
  for i in 0..$poolSize-1
    for j in 0..$ruleSize-1
      for k in 0..$locusSize-1
        gene[i][j][k].replace(("A".bytes.to_a[0] + setrnd(26)).chr)
      end
    end
  end
end

    
def score(singlerule, lines, lineno)
  score = 0
  for l in 0..lineno
    localscore = 0
    for i in 0..$locusSize-1
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
  for j in 0..$ruleSize-1
    fvalue += score(sgene[j], lines, lineno)
  end
  return fvalue
end


def printgene(gene, lines, lineno)
  for i in 0..$poolSize-1
    fvalue = fitness(gene[i], lines, lineno)
    if fvalue >= $lowerLimit then
      print i.to_s + " : "
      for j in 0..$ruleSize-1
        for k in 0..$locusSize-1
          print gene[i][j][k]
          if j < $ruleSize then
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
  
  for i in 0..$poolSize-1
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


def mutation(midgene)
  for i in 0..$poolSize-1
    for j in 0..$ruleSize-1
      for k in 0..$locusSize-1
        gene[i][j][k].replace(("A".bytes.to_a[0] + setrnd(26)).chr)
      end
    end
  end
end




gene = Array.new($poolSize){
  Array.new($ruleSize){
    Array.new($locusSize, " ")
  }
}

lines = Array.new($maxLines){
    Array.new($lineSize, "")
}

lineno = readlines(lines)
initgene(gene)
for generation in 0..$gMax
  puts "第" + generation.to_s + "世代平均適応度\t" + fave(gene, lines, lineno).to_s
  printgene(gene, lines, lineno)
  mutation(gene)
end
