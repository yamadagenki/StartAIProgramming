//	ai6.c
//      学習により語彙を増やす人工無能プログラム
//	元になるのは，形態素の連鎖により文を作成する人工無能プログラムai3.c
// および，形態素切り出しプログラムcutm_p.cプログラムです
//	形態素の連鎖が格納されたファイルmorph.txtを用います
// あらかじめ準備する形態素の切り出しにはcutm_p.cプログラムを使ってください．

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
  ++i ;
  if(i>=MAXNO){
   fprintf(stderr,"警告　形態素数を%d個に制限します\n",MAXNO);
   break ;
  }
 }
 /* ai3.cからの変更点*/
 fclose(fp) ;//ファイルを閉じる
 /* 変更点おわり*/
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

/*漢字かそれ以外かの判別*/
int iskanji(char ch)
{
 int d ;
 d=(unsigned char)ch ;
 if(d>=0x88) return 1 ;
 else return 0 ;
}

/* 開始文字列の決定*/
void setstartch(char *startch,char *line)
{
 unsigned int i,j;
 
 /*漢字以外の読み飛ばし*/
 for(i=0;i<strlen(line);i+=2)
  if(iskanji(line[i])==1) break ;
 if(i==strlen(line)){//漢字が見つからない
  strncpy(startch,"人工知能",MAXLINE) ;
 }
 else{
 /*漢字の抽出*/
 j=0 ;
 while((iskanji(line[i])==1)&&(line[i]!='\0')){
  startch[j++]=line[i++] ;
  startch[j++]=line[i++] ;
 }
 startch[j]='\0' ;
 }
}

/* 以下，ai3.cからの変更点*/
/*以下はcutm_p.cプログラムからの関数の追加*/
/*カタカナかそれ以外かの判別*/
int iskatakana(char ch1,char ch2)
{
 int d1,d2 ;
 d1=(unsigned char)ch1 ;
 d2=(unsigned char)ch2 ;
 if((d1==0x83)&&(d2>=40)&&(d2<=0x96)) return 1 ;
 else return 0 ;
}
/*字種の設定*/
int typeset(char ch1,char ch2)
{
 if(iskanji(ch1)) return 0 ;//漢字は０
 else if(iskatakana(ch1,ch2)) return 1 ;//カタカナは１
 else return 2 ;//その他は２
}
/*句読点の検出*/
int ispunct(char *ch)
{
 if((strncmp(ch,"．",2)==0)
  ||(strncmp(ch,"。",2)==0)
  ||(strncmp(ch,"，",2)==0)
  ||(strncmp(ch,"、",2)==0)
  ) return 1;//句読点なら１
  else return 0 ;
}
/*全角文字のみ取り出す*/
void getwidechar(char *t,char *s,int n)
{
 int in=0;//入力データのポインタ
 int out=0 ;//出力データのポインタ
 int d;
 while(in<n){
  d=(unsigned char)s[in] ;
  if(((d>0x7F)&&(d<0xA0))||(d>0xDF)&&(d<0xF0)){//２バイト文字
    t[out++]=s[in++];
    t[out++]=s[in++];
  }
  else ++in ;
 }
 t[out]='\0' ;//文字列の終端
}
/*ここまではcutm_p.cプログラムの関数の追加*/

/*形態素の切り出し*/
/*この関数は，cutm_p.cプログラムの同名の関数を改造したものです*/
void outputmorph(char *target,FILE *fp) 
{
 int i=0 ;
 int now,last;//漢字(0)・カタカナ(1)・その他(2)の別
 last=typeset(target[i],target[i+1]) ;
 while((target[i]!='\0')&& (i<MAXLINE)){
  if(ispunct(&(target[i]))==0){//句読点ではない
   /*文内の処理*/
   now=typeset(target[i],target[i+1]) ;
   if(now!=last) {//字種が変わっている
    putc('\n',fp) ;//区切りの改行を出力
    last=now ;
   }
   putc(target[i++],fp) ;
   putc(target[i++],fp) ;
  }
  else{//句読点
  /*文末などの処理*/
   putc('\n',fp) ;//区切りの改行を出力
   putc(target[i++],fp) ;
   putc(target[i++],fp) ;
   putc('\n',fp) ;//区切りの改行を出力
   last=typeset(target[i],target[i+1]) ;   
  } 
 }
}

/*利用者の入力から形態素ファイルを更新する*/
void addmorph(char line[])
{
 FILE *fp;
 char target[MAXLINE];

 if((fp=fopen(FILENAME,"a"))==NULL){
  fprintf(stderr,"エラー　ファイルmorph.txtのオープンに失敗しました\n");
  exit(1) ;
 }
 /*全角文字のみ取り出す*/
 getwidechar(target,line,strlen(line)) ;
 outputmorph(target,fp);//形態素の追加
 fclose(fp) ;
}
/*以上で，ai3.cプログラムからの変更点終わり*/
 
int main()
{
 char line[MAXLINE] ;//入力バッファ
 char db[MAXNO][2][MAXLINE] ;//形態素のデータベース
 int n ;//形態素の個数
 char startch[MAXLINE];//開始文字
 
 /*乱数の初期化*/
 srand(65535) ;

 /*オープニングメッセージ*/
 printf("さくら：メッセージをどうぞ\n");
 printf("あなた：");
 /*会話しましょう*/
 while(fgets(line,MAXLINE-1,stdin)!=NULL){
	 /* ai3.cからの変更点*/
	 addmorph(line) ;//利用者の入力により形態素ファイルを更新する
  /*形態素ファイルの読み込み*/
  n=readmorph(db) ;
  /*変更点終わり*/
  printf("さくら：");
  setstartch(startch,line) ;
  generates(startch,db,n) ;
  printf("あなた：");
 }
 /*エンディングメッセージ*/
 printf("さくら：ばいば～い\n");
 return 0 ;
}



