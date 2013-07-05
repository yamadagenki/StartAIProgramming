//	cutnav.c
//	字種に基づく名詞・形容詞・動詞・形容動詞の切り出し
//	テキストから全角データのみ抽出して終端記号を切り出します
//  使い方
//  　　cutnav （オプション）
//　オプションの与え方
//    nまたはなし		名詞の切り出し
//    v　　　			動詞の切り出し
//    a　　　			形容詞の切り出し
//    d      			形容動詞の切り出し

#include<stdio.h>
#include<string.h>
#define MAX 65535*3 //192kバイトまで処理可能
#define LENGTH 64//終端記号を仮に格納する変数のバイト数

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


/*名詞の切り出し*/
void outputnoun(char *target) 
{
 int i=0 ;
 int now,last;//漢字(0)・カタカナ(1)・その他(2)の別
 last=typeset(target[i],target[i+1]) ;
 while(target[i]!='\0'){
   now=typeset(target[i],target[i+1]) ;
   if((now!=last)&&(last==0)) {//漢字の終わり
    putchar('\n') ;//区切りの改行を出力
   }
   if(now==0){//漢字の出力
    putchar(target[i]) ;
    putchar(target[i+1]) ;
   }
   last=now ;
   i+=2 ;
 }
}

/*動詞・形容詞・形容動詞の切り出し*/
void outputp(char *target,char *str) 
{
 int i=0 ;
 int now,last;//漢字(0)・カタカナ(1)・その他(2)の別
 char k[LENGTH] ;//切り出し途中の文字列
 int klength=0 ;//kの長さ
 last=typeset(target[i],target[i+1]) ;
 if(last==0) {
  strncpy(k,&(target[i]),2) ;
  klength+=2 ;
 }
 i+=2 ;
 while(target[i]!='\0'){
   now=typeset(target[i],target[i+1]) ;
   if(now==0){//漢字を変数kに保存
	strncat(k,&(target[i]),2) ;
	klength+=2 ;
	k[klength]='\0' ;
   }
   if((now!=last)&&(last==0)){//漢字列の終わり
    if(strncmp(&(target[i]),str,2)==0) {
        //漢字の終わりにstrで指定した文字がある
     printf("%s%s\n",k,str) ;//終端記号を出力
    }
    klength=0 ;//切り出し文字のリセット
    k[klength]='\0' ;
   }
   last=now ;
   i+=2 ;
 }
}

int main(int argc,char **argv)
{
 char source[MAX] ;//入力データ
 char target[MAX] ;//全角データ
 int numchar ;//入力文字数

 /*テキストを読み込む*/
 numchar=getsource(source) ;

 /*全角文字のみ取り出す*/
 getwidechar(target,source,numchar) ;

 /*名詞の切り出し*/
 if(argc==1)
  outputnoun(target) ;			//名詞
 else if(strncmp(argv[1],"n",1)==0)
  outputnoun(target) ;			//名詞
 else if(strncmp(argv[1],"v",1)==0)
  outputp(target,"う") ;		//動詞
 else if(strncmp(argv[1],"a",1)==0)
  outputp(target,"い") ;		//形容詞
 else if(strncmp(argv[1],"d",1)==0)
  outputp(target,"だ") ;		//形容動詞

 return 0 ;
}

