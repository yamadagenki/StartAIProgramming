//	genbymorph.c
//	形態素解析プログラムcputm_p.cの出力した形態素の連鎖により文を作成する
//	形態素の連鎖が格納されたファイルmorph.txtを用います
//	開始文字列を指定すると文を生成します

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXNO 10000 //形態素連鎖の最大数
#define MAXLINE 48 //1行の最大バイト数
#define FILENAME "morph.txt" //形態素が格納されたファイル


/*形態素ファイルの読み込み*/
int readmorph(char db[MAXNO][2][MAXLINE])
{
 FILE *fp;
 char line[MAXLINE] ,oldline[MAXLINE];
 int i=0 ;

 if((fp=fopen(FILENAME,"r"))==NULL){
  fprintf(stderr,"エラー　ファイルmorph.txtがありません\n");
  exit(1) ;
 }
 fgets(oldline,MAXLINE,fp) ;
 if(strchr(oldline,'\n')!=NULL)*strchr(oldline,'\n')='\0' ;//改行コードを取り除く
 while(fgets(line,MAXLINE,fp)!=NULL){
  if(strchr(line,'\n')!=NULL) *strchr(line,'\n')='\0' ;//改行コードを取り除く
  strncpy(db[i][0],oldline,MAXLINE) ;//形態素をコピー
  strncpy(db[i][1],line,MAXLINE) ;//形態素をコピー
  strncpy(oldline,line,MAXLINE) ;
  printf("DEBUG %s %s\n",db[i][0],db[i][1]) ;
  ++i ;
  if(i>=MAXNO){
   fprintf(stderr,"警告　形態素数を%d個に制限します\n",MAXNO);
   break ;
  }
 }
 return i ;//形態素の個数を返す
}
/*開始文字が何回含まれるか数える*/
int findch(char *startch,char db[MAXNO][2][MAXLINE],int n) 
{
 int i ;
 int no=0 ;
 for(i=0;i<n;++i){
  if(strncmp(startch,db[i][0],MAXLINE)==0) ++ no ;
 }
 return no ;
}
/*num以下の乱数をセット*/
int setrnd(int num)
{
 int rndno ;
 while((rndno=(double)rand()/RAND_MAX*num)==num) ;
 return rndno ;

}

/*次の文字を形態素ＤBによりランダムにセット*/
void setrndstr(char *startch,char db[MAXNO][2][MAXLINE],int n)
{
  strncpy(startch,db[setrnd(n)][1],MAXLINE);
}

/*次の文字を形態素ＤＢによりセット*/
void setnext(char *startch,char db[MAXNO][2][MAXLINE],int n,int num) 
{
 int i ;
 int no=-1 ;
 int point ;
 
 point=setrnd(num) ;//num以下の乱数をセット
 for(i=0;i<n;++i){
  if(strncmp(startch,db[i][0],MAXLINE)==0) ++ no ;
  if(no==point){
   strncpy(startch,db[i][1],MAXLINE);
  break ;
  }
 }  
}


/*文の生成*/
void generates(char *startch,char db[MAXNO][2][MAXLINE],int n)
{
 int i,num ;

 /*開始文字列の出力*/
 printf("%s",startch) ;
  /*句点が出るまで繰り返し*/
 do{
  /*開始文字が何回含まれるか数える*/
  num=findch(startch,db,n) ;
  /*その中からランダムに文字列を選ぶ*/
  if(num!=0)
    setnext(startch,db,n,num) ;
  else
    setrndstr(startch,db,n) ;
  /*文字を出力する*/
  printf("%s",startch) ;
 }while((strncmp(startch,"．",2)!=0)&&(strncmp(startch,"。",2)!=0)) ;
 printf("\n") ;
}

int main()
{
 char db[MAXNO][2][MAXLINE] ;//形態素のデータベース
 int n ;//形態素の個数
 char startch[MAXLINE];//開始文字
 int i ;
 char workch[MAXLINE];//作業用の文字

 
 /*乱数の初期化*/
 srand(65535) ;
 /*形態素ファイルの読み込み*/
 n=readmorph(db) ;


 /*開始文字の決定*/
 printf("開始文字列を入力してください\n") ;
 fgets(startch,MAXLINE,stdin) ;
 if(strchr(startch,'\n')!=NULL) *strchr(startch,'\n')='\0' ;//改行コードを取り除く

 /*10回の文の生成*/
 for(i=0;i<10;++i){
    strcpy(workch,startch) ;
    generates(workch,db,n) ;
 }
 return 0 ;
}



