//	cutmorph.c
//	字種に基づく形態素の切り出し
//	テキストから全角データのみ抽出して形態素を切り出します

#include<stdio.h>
#include<string.h>
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

/*漢字かそれ以外かの判別*/
int iskanji(char ch)
{
 int d ;
 d=(unsigned char)ch ;
 if(d>=0x88) return 1 ;
 else return 0 ;
}
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
 /*形態素の切り出し*/
void outputmorph(char *target) 
{
 int i=0 ;
 int now,last;//漢字(0)・カタカナ(1)・その他(2)の別
 last=typeset(target[i],target[i+1]) ;
 while(target[i]!='\0'){
  if(ispunct(&(target[i]))==0){//句読点ではない
   /*文内の処理*/
   now=typeset(target[i],target[i+1]) ;
   if(now!=last) {//字種が変わっている
    putchar('\n') ;//区切りの改行を出力
    last=now ;
   }
   putchar(target[i++]) ;
   putchar(target[i++]) ;
  }
  else{//句読点
  /*文末などの処理*/
   putchar('\n') ;//区切りの改行を出力
   ++i;++i;//句読点の読み飛ばし
   last=typeset(target[i],target[i+1]) ;   
  } 
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

 /*形態素の切り出し*/
 outputmorph(target) ;

 return 0 ;
}

