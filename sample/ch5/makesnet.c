//	makesnet.c
//	意味ネットワークの作成
//	テキストデータから意味ネットワークを作ります
// 語の並びを記述したファイル kk.txtが必要です

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXNUM 4096 //意味ネットワークの最大個数
#define MAXLINE 64 //１文の最大長さ
#define NOPOS -1 //探索失敗の場合の値
#define FILENAME  "kk.txt" //読み込み対象ファイル

/*テキストを読み込む*/
int getsource(char semnet[MAXNUM][2][MAXLINE] )
{
 int numsnet=0 ;
 char line[MAXLINE] ; //読み込み用バッファ
 FILE *fp;
 
 if((fp=fopen(FILENAME,"r"))==NULL){
  fprintf(stderr,"エラー　ファイル%sがありません\n",FILENAME);
  exit(1) ;
 }
 /*読み込み処理*/
 while(fscanf(fp,"%s",line)!=EOF){
  strncpy(semnet[numsnet][0],line,MAXLINE) ;//「～は」にあたる部分
  if(fscanf(fp,"%s",line)!=EOF){
   strncpy(semnet[numsnet][1],line,MAXLINE) ;//「～，」にあたる部分
  }
  else break ;//最後に1個あまった場合
  ++numsnet ;
  if(numsnet>=MAXNUM){//ネットワーク数が上限を超えている
	  --numsnet ;
	  printf("警告　意味ネットワークの数を%dに制限しました\n",numsnet) ;
	  break ;
	 }
 }
 return numsnet ;
}
/*意味ネットワークの探索*/
int searchword(char semnet[MAXNUM][2][MAXLINE],int numsnet,char line[],int flag[])
{
	int i ;
	for(i=0;i<numsnet;++i){
  if((strcmp(semnet[i][0],line)==0)&&(flag[i]==0)){//見つけた
   flag[i]=1 ;//2回使わないようにする
	  break ;
	 }
 }
 if(i>=numsnet) i=NOPOS ;//見つからなかった
		
 return i ;
}


/* 連想の処理*/
void searchsnet(char semnet[MAXNUM][2][MAXLINE],int numsnet,char line[])
{
	int pos ;
	int i ;
	int flag[MAXNUM] ;//2度使わないためのフラグ

	for(i=0;i<MAXNUM;++i) flag[i]=0 ;//flag[]の初期化
 while((pos=searchword(semnet,numsnet,line,flag))!=NOPOS){
 	printf("%sは%s，\n",line,semnet[pos][1]) ;//連想の出力
	 strncpy(line,semnet[pos][1],MAXLINE) ;
 }
 printf("%sは・・・わからない！\n",line) ;//見つからないので終了
}

int main()
{
 char semnet[MAXNUM][2][MAXLINE] ;//意味ネットワーク
 int numsnet ;//意味ネットワークの数
 char line[MAXLINE] ;//入力バッファ

 /*テキストを読み込む*/
 numsnet=getsource(semnet) ;
 printf("%d個の意味ネットワークを読み込みました\n",numsnet) ;

 /*意味ネットワークを検索する*/
 printf("連想を開始する単語を入力してください．\n");
 /*連想しましょう*/
 while(scanf("%s",line)!=EOF){
  searchsnet(semnet,numsnet,line) ;
  printf("連想を開始する次の単語を入力してください．\n");
 }
 printf("処理を終わります．\n");

 return 0 ;
}

