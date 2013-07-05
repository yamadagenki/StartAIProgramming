//      ai5.c
//	プロダクションルールを用いた人工無能
//      プロダクションルールを記述したファイル rule.txtが必要です

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXNO 32 //プロダクションルールの最大個数
#define MAXSTR 64 //文字列の最大長さ
#define MAXLINE 256 //1行のの最大長さ
#define NORULE -1//ルールにマッチしない場合の戻り値

#define FILENAME  "rule.txt" //読み込み対象ファイル

/*　プロダクションルールを格納する構造体*/
struct prule{
 char str1[MAXSTR] ;// 条件1
 char str2[MAXSTR] ;// 条件2
 char str3[MAXSTR] ;// 条件3
 char str4[MAXSTR] ;// 条件4

 char action[MAXSTR] ;//行動（応答文字列）
} ;

/*num以下の乱数をセット*/
int setrnd(int num)
{
 int rndno ;
 while((rndno=(double)rand()/RAND_MAX*num)==num) ;
 return rndno ;
}

/* 入力にマッチするルールを探す*/
int rulematch(struct prule rule[MAXNO] ,int i,char *line)
{
	if((strstr(line,rule[i].str1)!=NULL) &&
	   (strstr(line,rule[i].str2)!=NULL) &&
	   (strstr(line,rule[i].str3)!=NULL) &&
	   (strstr(line,rule[i].str4)!=NULL))
	  return 1 ;//合致した
	else 
	return  0;//合致しない
}

/* 応答文の生成 */
void answer(struct prule rule[MAXNO] ,int n,char *line)
{
	int i,limit,no=0,point=0 ;

	for(i=0;i<n;++i){// マッチするルールの個数を調べる
   no+=rulematch(rule,i,line) ;
 }

 if(no==0) printf("どうぞ続けてください\n") ;//マッチするルールがない
 else{//少なくとも１つはマッチするルールがある
	 limit=setrnd(no) ;//競合解消，limit番目のルールを採用
	 for(i=0;i<n;++i){//ルールを改めて検索する
		 if(rulematch(rule,i,line)==1){
			 if(point==limit) break ;//limit番目の適合ルールを発見
			 ++point ;
		 }
		} 
	 printf("%s\n",rule[i].action) ;//行動（返答文の出力）
 }
}

/*テキストを読み込む*/
int readrule(struct prule rule[MAXNO] )
{
 int n=0 ;
 char line[MAXSTR] ; //読み込み用バッファ
 FILE *fp;
 
 if((fp=fopen(FILENAME,"r"))==NULL){
  fprintf(stderr,"エラー　ファイル%sがありません\n",FILENAME);
  exit(1) ;
 }
 /*読み込み処理*/
 while(fgets(line,MAXLINE,fp)!=NULL){
	 sscanf(line,"%s %s %s %s %s",rule[n].str1,rule[n].str2,
	                  rule[n].str3,rule[n].str4,rule[n].action) ;
	 if(strlen(rule[n].str1)>1){//少なくとも条件がひとつ以上ある
 	 if(strcmp(rule[n].str2,"-")==0) strcpy(rule[n].str2,rule[n].str1) ;
	  if(strcmp(rule[n].str3,"-")==0) strcpy(rule[n].str3,rule[n].str2) ;
	  if(strcmp(rule[n].str4,"-")==0) strcpy(rule[n].str4,rule[n].str3) ;
  }
  ++n ;
  if(n>=MAXNO){//ルール数が上限を超えている
	  --n ;
	  printf("警告　ルール数を%dに制限しました\n",n) ;
	  break ;
	 }
 }
 return n ;
}

int main()
{
 char line[MAXLINE] ;//入力バッファ
 struct prule rule[MAXNO] ;//プロダクションルール
 int n ;//ルールの数
 
 /*乱数の初期化*/
 srand(65535) ;
 /*プロダクションルールファイルの読み込み*/
 n=readrule(rule) ;

 /*オープニングメッセージ*/
 printf("さくら：さて，どうしました？\n");
 printf("あなた：");
 /*会話しましょう*/
 while(fgets(line,MAXLINE,stdin)!=NULL){
  printf("さくら：");
  answer(rule,n,line) ;//プロダクションルールによる応答文生成
  printf("あなた：");
 }
 /*エンディングメッセージ*/
 printf("さくら：それではお話を終わりましょう\n");
 return 0 ;
}

