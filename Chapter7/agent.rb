# -*- coding: utf-8 -*-
$gu = 0
$cyoki = 1
$pa = 2

initVal = 10.to_i

$handsFileName = "hands.txt"
$maxLine = 256
$fileName = "int.txt"


def setrnd(num)
  return rand(num)
end

def learning(reward, last_my, last_opp, q, fp)
  for i in 0..2
    if i==last_my then
      alpha = 1
    else
      alpha = -1
    end
    if q[last_opp][i] + alpha * reward > 0 then
      q[last_opp][i] += alpha * reward
    end
  end

  for i in 0..2
    for j in 0..2
      fp.print q[i][j].to_s + " "
    end
  end
  fp.puts ""
end

def roulette(pq)
  point = 0
  acc = 0
  step = setrnd(pq[0] + pq[1] + pq[2])
  while acc <= step do
    acc += pq[point]
    point += 1
  end
  return point - 1
end

def selectaction(opphand, q)
  return roulette(q[opphand])
end

def setreward(opphand, last_my)
  # p opphand.to_s + " " + last_my.to_s
  rtable = Array.new([[0,-1,1],[1,0,-1],[-1,1,0]])
  return rtable[opphand][last_my]
end


def printFunc(y)
  if y==0 then
    print "GU"
  elsif y == 1 then
    print "CYOKI"
  else
    print "PA"
  end
end

#main

line = Array.new($maxLine){
  ""
}

q = Array.new([[initVal,initVal,initVal],[initVal,initVal,initVal],[initVal,initVal,initVal]])
fp = File.open($fileName, 'w')

handsfp = File.open($handsFileName, 'r')

last_my = $gu.to_i
last_opp = $gu.to_i

while line = handsfp.gets

  opphand = line.chomp.to_i
  
  reward = setreward(opphand, last_my)
  if reward != 0 then
    learning(reward, last_my, last_opp, q, fp)
    printFunc(opphand)
    print " " + reward.to_s + " "
     last_my=selectaction(opphand,q)
    printFunc(last_my)
    puts ""
    last_opp = opphand
  end
end
