// 強化学習によるじゃんけんエージェントプログラム(環境つき）agent.c
// このプログラムは，じゃんけんエージェントと環境の両方の機能を果たします
// 実行するには，環境がエージェントに与える手の系列を格納したファイルhands.txtが必要です
// agentプログラムがおかれたディレクトリには，内部状態の途中経過を保存するファイルint.txtが作成されます

#include<stdio.h>
#include<stdlib.h>
#define MAXLINE 256
#define GU 0    //グー
#define CYOKI 1 //チョキ
#define PA 2   //パー
#define INITVAL 10 //戦略表の初期値
#define FILENAME "int.txt" //内部状態の途中経過を保存するファイル
#define HANDSFILENAME "hands.txt" //環境がエージェントに与える手の系列を格納したファイル

/*num以下の乱数をセット*/
int setrnd(int num)
{
 int rndno ;
 while((rndno=(double)rand()/RAND_MAX*num)==num) ;
 return rndno ;

}

/*学習*/
void learning(int reward,int last_my,int last_opp,int q[3][3],FILE *fp)
{
 int i,j,alpha ;
 for(i=0;i<3;++i){
  if(i==last_my) alpha=1 ;
  else alpha=-1 ;
  /*報酬に基づいてqを更新*/
  if((q[last_opp][i]+alpha*reward)>0) q[last_opp][i]+=alpha*reward ;
  }
  /*ファイルへの内部状態の書き出し*/
  for(i=0;i<3;++i)
   for(j=0;j<3;++j)
    fprintf(fp,"%d ",q[i][j]) ;
  fprintf(fp,"\n") ;
}
/*ルーレットを回して手を選ぶ*/
int roulette(int pq[3])
{
 int step ;//ルーレットの値
 int acc=0 ;//適応度の積算値
 int point=0;

 step=setrnd(pq[0]+pq[1]+pq[2]);//ルーレットの値を決定
 while(acc<=step){
  acc+=pq[point] ;
  ++point ;
 }
 return point-1 ;
}

/* 行動選択（手の決定）*/
int selectaction(int opphand,int q[3][3])
{
 return roulette(q[opphand]) ;
}

/*報酬の設定*/
int setreward(int opphand,int last_my)
{
 int rtable[3][3]={{0,-1,1},{1,0,-1},{-1,1,0}} ;
 return rtable[opphand][last_my] ;
}

int main()
{
 char line[MAXLINE] ;//入力バッファ
 int opphand,last_opp ;//相手の手
 int myhand,last_my ;//自分の手
 int reward ;//報酬
 int q[3][3]={{INITVAL,INITVAL,INITVAL},
                   {INITVAL,INITVAL,INITVAL},
                   {INITVAL,INITVAL,INITVAL}} ;//戦略表
 FILE *fp;//途中経過を格納するファイルのファイルポインタ
 FILE *handsfp;//環境の手の系列ファイルのファイルポインタ

 if((fp=fopen(FILENAME,"w"))==NULL){
  fprintf(stderr,"エラー　ファイル%sを開けません\n");
  exit(1) ;
 }
 
 if((handsfp=fopen(HANDSFILENAME,"r"))==NULL){
  fprintf(stderr,"エラー　ファイルを開けません\n");
  exit(1) ;
 }
 
 srand(32767);//乱数の初期化
 last_my=last_opp=GU ;//最初はグー
 /*じゃんけんの繰り返し*/
 while(fgets(line,MAXLINE,handsfp)!=NULL){//最初に前回の手を読む
  sscanf(line,"%d",&opphand) ;
  reward=setreward(opphand,last_my) ;//報酬の設定
  if(reward!=0) learning(reward,last_my,last_opp,q,fp) ;//報酬に基づく学習
  printf("%d %d ",opphand,reward) ;//前回の結果の出力
  printf("%d\n",(last_my=selectaction(opphand,q))) ;//次の行動を決定する
  last_opp=opphand ;//前回の手を覚えておく
 }

 return 0 ;
}
