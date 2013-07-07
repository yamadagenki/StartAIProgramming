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
  for l in 0..lineno - 1
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
  fpenalty=0
  for j in 0..$ruleSize-1
    sscore = score(sgene[j],lines,lineno)
    fpenalty += sscore*sscore
    fvalue += sscore
  end
  if fvalue > lineno then
    fvalue = lineno
  end
  totalfitness = fvalue**2 - fpenalty
  if totalfitness < 0 then
    totalfitness = 0
  end
  return totalfitness
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
  for i in 0..$poolSize*2-1
    for j in 0..$ruleSize-1
      for k in 0..$locusSize-1
        midgene[i][j][k].replace(("A".bytes.to_a[0] + setrnd(26)).chr)
      end
    end
  end
end

def setfvalue(midgene, fvalue, lines, lineno)
  for i in 0..$poolSize*2-1
    fvalue[i] = fitness(midgene[i],lines, lineno)+1
  end
end

def sumupfvalue(fvalue)
  sum = 0
  for i in 0..$poolSize*2-1
    sum += fvalue[i]
  end
  return sum
end

def roulette(fvalue, sumf, point)
  acc = 0
  point = 0
  step = setrnd(sumf)
  while acc < step do
    point = (point+1)%($poolSize*2)
    acc += fvalue[point]
  end
  fvalue[point] = 0
  return point
end

def selection(gene, midgene, lines, lineno)
  fvalue = Array.new($poolSize*2){ 0 }

  point = 0

  setfvalue(midgene, fvalue, lines, lineno)
  sumf = sumupfvalue(fvalue)
  for i in 0..$poolSize-1
    midpoint = roulette(fvalue, sumf, point)
    for j in 0..$ruleSize-1
      for k in 0..$locusSize-1
        gene[i][j][k] = midgene[midpoint][j][k];
      end
    end
  end
end

def groulette(fvalue, sumf, point)
  acc = 0
  step = setrnd(sumf)
  while acc < step do
    point = (point+1)%$poolSize
    acc += fvalue[point]
  end
  return point
end

def singlecrossover(p1, p2, c1, c2)
  for j in 0..$ruleSize - 1
    for k in 0..$locusSize -1
      if setrnd(2) > 0 then
        c1[j][k] = p1[j][k]
        c2[j][k] = p2[j][k]
      else
        c1[j][k] = p2[j][k]
        c2[j][k] = p1[j][k]
      end
    end
  end
end


def crossover(midgene, gene, lines, lineno)
  gfvalue = Array.new($poolSize){ 0 }
  for i in 0..$poolSize-1
    gfvalue[i] = fitness(gene[i], lines, lineno) + 1
  end
  gsumf = 0
  point = 0
  for i in 0..$poolSize-1
    gsumf += gfvalue[i]
  end

  for i in 0..$poolSize-1
    singlecrossover(gene[point=groulette(gfvalue, gsumf, point)], gene[point=groulette(gfvalue,gsumf,point)],midgene[2*i],midgene[2*i+1])
  end

end

gene = Array.new($poolSize){
  Array.new($ruleSize){
    Array.new($locusSize){""}
  }
}

midgene = Array.new($poolSize*2){
  Array.new($ruleSize){
    Array.new($locusSize){""}
  }
}


lines = Array.new($maxLines){
  Array.new($lineSize){""}
}

lineno = readlines(lines)
initgene(gene)
for generation in 0..$gMax-1
  puts "第" + generation.to_s + "世代平均適応度\t" + fave(gene, lines, lineno).to_s
  # printgene(gene, lines, lineno)
  crossover(midgene, gene, lines, lineno)
  mutation(midgene)
  selection(gene,midgene,lines,lineno)
end
  puts "第" + $gMax + "世代平均適応度\t" + fave(gene, lines, lineno).to_s
  printgene(gene, lines, lineno)

