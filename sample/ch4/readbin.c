//	バイナリファイル読み取りプログラム　readbin.c
// バイナリファイルを読み込んで画面に値を出力します
//　使い方　readbin ファイル名

#include<stdio.h>
#include<stdlib.h>

int main(int argc,char **argv)
{
 int ch;//入力バッファ
 FILE *fp ;

 if(argc!=2){//ファイル名が指定されていない
  fprintf(stderr,"使い方　readbin ファイル名\n");
  exit(1) ;
 }
 if((fp=fopen(argv[1],"rb"))==NULL){//ファイルが開けない
  fprintf(stderr,"エラー　ファイル%sをオープンできません\n",argv[1]);
  exit(1) ;
 }
 while((ch=getc(fp))!=EOF){
	 if((ch>=32)&&(ch<=127))//英数記号の範囲
   printf("%u\t%c\n",ch,ch) ;//バイナリデータの値と，文字としての出力
  else
   printf("%u\n",ch) ;//バイナリデータの値の出力
 }

 
 return 0 ;
}
