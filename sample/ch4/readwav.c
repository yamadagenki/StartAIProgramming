//	wavファイル読み取りプログラム　readwav.c
//	wavファイルから数値が並んだテキストファイルを生成します
//　wavファイルは8bit 8KHzサンプリング　モノラル専用です
//　使い方　readwav ファイル名

#include<stdio.h>
#include<stdlib.h>

/*dataチャンクまで読み飛ばす*/
void skipheader(FILE *fp)
{
 char ch1=' ',ch2=' ',ch3=' ',ch4 ;
 while((ch4=getc(fp))!=EOF){
  if((ch4=='a')&&(ch3=='t')&&(ch2=='a')&&(ch1=='d')) break ;
  ch1=ch2 ;ch2=ch3;ch3=ch4 ;
 }
 getc(fp) ;getc(fp);getc(fp);getc(fp);//バイト数の読み飛ばし
}

 
int main(int argc,char **argv)
{
 int ch;//入力バッファ
 FILE *fp ;

 if(argc!=2){//ファイル名が指定されていない
  fprintf(stderr,"使い方　readwav ファイル名\n");
  exit(1) ;
 }
 if((fp=fopen(argv[1],"rb"))==NULL){//ファイルが開けない
  fprintf(stderr,"エラー　ファイル%sをオープンできません\n",argv[1]);
  exit(1) ;
 }
 skipheader(fp) ;//dataチャンクまで読み飛ばす
 while((ch=getc(fp))!=EOF){
  printf("%u\n",ch) ;//音データの出力
 }

 
 return 0 ;
}
