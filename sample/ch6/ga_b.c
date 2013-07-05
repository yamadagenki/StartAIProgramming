//	遺伝的アルゴリズムによる探索プログラム  ga_b.c
// ga_aと評価方法が異なります(fitness関数が異なります）


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define POOLSIZE 30  //プールサイズ
#define RULESIZE 4  //遺伝子の持つルールの数
#define LOCUSSIZE 4 //ひとつのルールが持つ遺伝子座の数

#define GMAX 3000 //打ち切り世代
#define MRATE 0.1 //突然変異率

#define LOWERLIMIT 1000 //遺伝子を印字する最低適応度
#define MAXLINES 64 //キーワードの組み合わせの最大数
#define LINESIZE 64 //キーワードデータの行サイズ

/*num以下の乱数をセット*/
int setrnd(int num)
{
 int rndno ;
 while((rndno=(double)rand()/RAND_MAX*num)==num) ;
 return rndno ;

}

/*遺伝子プールの初期化*/
void initgene(char gene[POOLSIZE][RULESIZE][LOCUSSIZE])
{
 int i,j,k ;
 for(i=0;i<POOLSIZE;++i)
  for(j=0;j<RULESIZE;++j)
   for(k=0;k<LOCUSSIZE;++k)
    gene[i][j][k]='A'+setrnd(26) ;//ランダムに初期値をセット
}

/*ルールが何回データとマッチするかを計算*/
int score(char *singlerule,char lines[MAXLINES][LINESIZE],int lineno)
{
 int i,l ;
 int score=0 ;//マッチしたデータの行数
 int localscore ;
 for(l=0;l<lineno;++l){
  localscore=0 ;
  for(i=0;i<LOCUSSIZE;++i)//各キーワードを調べる
   if(strchr(lines[l],singlerule[i])!=NULL) ++localscore ;
  if(localscore>=LOCUSSIZE) ++score ;//完全に一致
 }
 return score ;
}

/*i番目の染色体の適応度を計算*/
int fitness(char sgene[RULESIZE][LOCUSSIZE],char lines[MAXLINES][LINESIZE],int lineno)
{
 int j,fvalue=0,fpenalty=0,sscore,totalfitness ;
 for(j=0;j<RULESIZE;++j){ 
  sscore=score(sgene[j],lines,lineno) ;
  fpenalty+=sscore*sscore ;
  fvalue+=sscore ;
 }
 if(fvalue>=lineno) fvalue=lineno ;//上限を総ルール数に制限
 totalfitness=fvalue*fvalue-fpenalty ;
 if(totalfitness<0) totalfitness=0 ;
 return totalfitness ;
}

/*遺伝子プールの出力*/
void printgene(char gene[POOLSIZE][RULESIZE][LOCUSSIZE],char lines[MAXLINES][LINESIZE],int lineno)
{
 int i,j,k ;
 int fvalue ;
 for(i=0;i<POOLSIZE;++i){
  fvalue=fitness(gene[i],lines,lineno) ;
  if(fvalue>=LOWERLIMIT){//この条件を変更すると表示量を調整できます
   printf("%3d : ",i) ;
   for(j=0;j<RULESIZE;++j){
    for(k=0;k<LOCUSSIZE;++k)
     printf("%c ",gene[i][j][k]) ;
    if(j<RULESIZE-1) printf(", ") ;
   }
   printf("     %d\n",fvalue) ;//適応度の出力
  }
 }
}
/*遺伝子プールの世代平均適応度の計算*/
double fave(char gene[POOLSIZE][RULESIZE][LOCUSSIZE],char lines[MAXLINES][LINESIZE],int lineno)
{
 int i ;
 double fsum=0.0 ;
 for(i=0;i<POOLSIZE;++i){
  fsum+=fitness(gene[i],lines,lineno) ;
 }
 return fsum/POOLSIZE ;
}

/*キーワードデータの読み込み*/
int readlines(char lines[MAXLINES][LINESIZE])
{
 int n=0 ;

 /*読み込み処理*/
 while(fgets(lines[n++],LINESIZE,stdin)!=NULL){
  if(n>=MAXLINES){//行数が上限を超えている
   --n ;
   printf("警告　行数を%dに制限しました\n",n) ;
   break ;
  }
  if(strlen(lines[n-1])<=2){//キーワードの記述されていない行の処理
   --n;
   break ;
  }
 }
 return n ;
}
/*突然変異*/
void mutation(char midgene[POOLSIZE*2][RULESIZE][LOCUSSIZE])
{
 int i,j,k ;

 for(i=0;i<POOLSIZE*2;++i)
   for(j=0;j<RULESIZE;++j)
    for(k=0;k<LOCUSSIZE;++k){
     if(setrnd(1.0/MRATE)<1){
      midgene[i][j][k]='A'+setrnd(26) ;//突然変異
     }
    }
}


/*midgeneプールの適応度の計算*/
void setfvalue(char midgene[POOLSIZE*2][RULESIZE][LOCUSSIZE],
            int fvalue[],char lines[MAXLINES][LINESIZE],int lineno)
{
 int i ;
 for(i=0;i<POOLSIZE*2;++i)
  fvalue[i]=fitness(midgene[i],lines,lineno)+1 ;
}

/*適応度の合計の計算*/
int sumupfvalue(int fvalue[])
{
 int i;
 int sum=0 ;
 for(i=0;i<POOLSIZE*2;++i)
  sum+=fvalue[i] ;
 return sum ;
}

/*ポインタのインクリメント*/
int incpoint(int point)
{
 ++point ;
 if(point>=POOLSIZE*2) point=0 ;//はじめに戻す
 return point ;
}
	
/*ルーレットを回してひとつ遺伝子を選ぶ*/
int roulette(int fvalue[POOLSIZE*2],int sumf,int point)
{
 int step ;//ルーレットの値
 int acc=0 ;//適応度の積算値

 step=setrnd(sumf);//ルーレットの値を決定
 while(acc<step){
  point=incpoint(point) ;
  acc+=fvalue[point] ;
 }
 fvalue[point]=0 ;//２度選ばれないようにする
 return point ;
}

/*選択*/
void selection(char gene[POOLSIZE][RULESIZE][LOCUSSIZE],char midgene[POOLSIZE*2][RULESIZE][LOCUSSIZE],
   char lines[MAXLINES][LINESIZE],int lineno)
{
 int i,j,k ;
 int fvalue[POOLSIZE*2] ;//midgeneプールの適応度
 int sumf ;//適応度の合計値
 int point=0 ;//ルーレットのスタート場所
 int midpoint ;
 
 setfvalue(midgene,fvalue,lines,lineno) ;//fvalueに値をセット
 sumf=sumupfvalue(fvalue) ;//適応度の合計値を計算
 for(i=0;i<POOLSIZE;++i){//ルーレットにしたがって選択
  midpoint=roulette(fvalue,sumf,point) ;
  for(j=0;j<RULESIZE;++j)
   for(k=0;k<LOCUSSIZE;++k)
    gene[i][j][k]=midgene[midpoint][j][k]; 
 }
}

/*ポインタのインクリメント(groulette用）*/
int gincpoint(int point)
{
 ++point ;
 if(point>=POOLSIZE) point=0 ;//はじめに戻す
 return point ;
}
	
/*ルーレットを回してひとつ遺伝子を選ぶ(交叉用）*/
int groulette(int fvalue[POOLSIZE],int sumf,int point)
{
 int step ;//ルーレットの値
 int acc=0 ;//適応度の積算値

 step=setrnd(sumf);//ルーレットの値を決定
 while(acc<step){
  point=gincpoint(point) ;
  acc+=fvalue[point] ;
 }
// fvalue[point]=0 ;//２度選ばれても良い
 return point ;
}

/*一様交叉*/
void singlecrossover(char p1[RULESIZE][LOCUSSIZE],char p2[RULESIZE][LOCUSSIZE],
                char c1[RULESIZE][LOCUSSIZE],char c2[RULESIZE][LOCUSSIZE])
{
	int j,k ;

 for(j=0;j<RULESIZE;++j){
  for(k=0;k<LOCUSSIZE;++k){
   if(setrnd(2)>0){
    c1[j][k]=p1[j][k]; 
    c2[j][k]=p2[j][k];
   }
   else{
    c1[j][k]=p2[j][k]; 
    c2[j][k]=p1[j][k];
   }
  }
 }
}

/*交叉*/
void crossover(char midgene[POOLSIZE*2][RULESIZE][LOCUSSIZE],char gene[POOLSIZE][RULESIZE][LOCUSSIZE]
                ,char lines[MAXLINES][LINESIZE],int lineno)
{
 int i,j,k ;
 int gfvalue[POOLSIZE] ;//geneプールの適応度
 int gsumf=0 ;//適応度の合計値
 int point=0 ;//ルーレットのスタート場所
 int midpoint ;
 
 for(i=0;i<POOLSIZE;++i)
  gfvalue[i]=fitness(gene[i],lines,lineno)+1 ;//fvalueに値をセット
 for(i=0;i<POOLSIZE;++i)
  gsumf+=gfvalue[i] ;//適応度の合計値を計算
 for(i=0;i<POOLSIZE;++i){//ルーレットにしたがって選択
  singlecrossover(gene[point=groulette(gfvalue,gsumf,point)],
                  gene[point=groulette(gfvalue,gsumf,point)],
                  midgene[2*i],midgene[2*i+1]) ;
 }

}


int main()
{
 char gene[POOLSIZE][RULESIZE][LOCUSSIZE] ;//遺伝子プール
 char midgene[POOLSIZE*2][RULESIZE][LOCUSSIZE] ;//増殖中の遺伝子プール
 char lines[MAXLINES][LINESIZE] ;//キーワードのデータ
 int lineno ;//キーワードデータの行数
 int generation ;
 srand(0) ;//乱数の初期化
 lineno=readlines(lines) ;//キーワードデータの読み込み
 initgene(gene) ;//遺伝子プールの初期化
 for(generation=0;generation<GMAX;++generation){
  printf("第%d世代 平均適応度 %f\n",generation,fave(gene,lines,lineno)) ;
  printgene(gene,lines,lineno) ;//遺伝子プールの出力
  crossover(midgene,gene,lines,lineno) ;//交叉
  mutation(midgene) ;//突然変異
  selection(gene,midgene,lines,lineno) ;//選択
 }
  printf("第%d世代 平均適応度 %f\n",generation,fave(gene,lines,lineno)) ;
  printgene(gene,lines,lineno) ;//遺伝子プールの出力

 return 0 ;
}
