//	cutkk.c
//	漢字やカタカナ語の抽出
//	テキストデータから，漢字やカタカナによる語を抽出します

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
 char w[3] ;
 w[0]=ch1; w[1]=ch2; w[2]='\0' ;
 d1=(unsigned char)ch1 ;
 d2=(unsigned char)ch2 ;
 if((d1==0x83)&&(d2>=40)&&(d2<=0x96)) return 1 ;
 if(strncmp(w,"ー",2)==0) return 1 ;//長音記号だけ特別扱い
 else return 0 ;
}
/*字種の設定*/
int typeset(char ch1,char ch2)
{
 if(iskanji(ch1)) return 0 ;//漢字は０
 else if(iskatakana(ch1,ch2)) return 1 ;//カタカナは１
 else return 2 ;//その他は２
}


/*語の切り出し*/
void outputmorph(char *target) 
{
 int i=0 ;
 int now,last;//漢字(0)・カタカナ(1)・その他(2)の別
 last=typeset(target[i],target[i+1]) ;
 while(target[i]!='\0'){
   now=typeset(target[i],target[i+1]) ;
   if((now==0)||(now==1)){//漢字かカタカナ
    putchar(target[i++]) ;
    putchar(target[i++]) ;
   }
   else i+=2 ;//漢字・カタカナ以外の読み飛ばし
   if((now!=last)&&(last!=2)) {//字種が変わっている
    putchar('\n') ;//区切りの改行を出力
   }
   last=now ;
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

 /*語の切り出し*/
 outputmorph(target) ;

 return 0 ;
}

