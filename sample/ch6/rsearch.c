//	ランダムサーチプログラム  rsearch.c
//	ランダムサーチにより解を探索します


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define POOLSIZE 30  //プールサイズ
#define RULESIZE 4  //遺伝子の持つルールの数
#define LOCUSSIZE 4 //ひとつのルールが持つ遺伝子座の数

#define GMAX 10000 //打ち切り世代
#define MRATE 0.1 //突然変異率

#define LOWERLIMIT 0 //遺伝子を印字する最低適応度
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
 int j,fvalue=0 ;
 for(j=0;j<RULESIZE;++j) 
  fvalue+=score(sgene[j],lines,lineno) ;
 return fvalue ;
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
void mutation(char gene[POOLSIZE][RULESIZE][LOCUSSIZE])
{
 int i,j,k ;

 for(i=0;i<POOLSIZE;++i)
  for(j=0;j<RULESIZE;++j)
   for(k=0;k<LOCUSSIZE;++k){
    if(setrnd(1.0/MRATE)<1){
     gene[i][j][k]='A'+setrnd(26) ;//突然変異
    }
   }
}

int main()
{
 char gene[POOLSIZE][RULESIZE][LOCUSSIZE] ;//遺伝子プール
 char lines[MAXLINES][LINESIZE] ;//キーワードのデータ
 int lineno ;//キーワードデータの行数
 int generation ;
 srand(65535) ;//乱数の初期化
 lineno=readlines(lines) ;//キーワードデータの読み込み
 initgene(gene) ;//遺伝子プールの初期化
 for(generation=0;generation<GMAX;++generation){
  printf("第%d世代 平均適応度 %f\n",generation,fave(gene,lines,lineno)) ;
  printgene(gene,lines,lineno) ;//遺伝子プールの出力
  mutation(gene) ;//突然変異
 }
 return 0 ;
}
