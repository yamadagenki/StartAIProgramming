//	make3gram.c
//	3-gramデータの作成
//	テキストから全角データのみ抽出して3-gramを作ります

#include<stdio.h>
#define MAX 65535*3 //192kバイトまで処理可能

/*テキストを読み込む*/
int getsource(char *s)
{
 int n=0 ;//文字数のカウンタ

 while((s[n++]=getchar())!=EOF) ;
 return n ;
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

 /*3-gramの出力*/
void outputtarget(char *target) 
{
 int i=0 ;
 while((target[i]!='\0')&&(target[i+2]!='\0')&&(target[i+4]!='\0')){
  putchar(target[i++]) ;
  putchar(target[i++]) ;
  putchar(target[i]) ;
  putchar(target[i+1]) ;
  putchar(target[i+2]) ;
  putchar(target[i+3]) ;
  putchar('\n') ;
 }
}

int main()
{
 char source[MAX] ;//入力データ
 char target[MAX] ;//全角データ
 int numchar ;//入力文字数

 /*テキストを読み込む*/
 numchar=getsource(source) ;

 /*全角文字のみ取り出す*/
 getwidechar(target,source,numchar) ;

 /*3-gramの出力*/
 outputtarget(target) ;

 return 0 ;
}

