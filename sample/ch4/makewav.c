//	wavファイル生成プログラム　makewav.c
//	数値が並んだテキストファイルからwavファイルを生成します
// 生成するwavファイルは8bit 8KHzサンプリング　モノラルです
//  ヘッダ は44バイト，データチャンクは可変長です
//  使い方  makewav 出力ファイル名 < 音声データテキストファイル

#include<stdio.h>
#include<stdlib.h>
#define MAX 8000*40 //40秒分のデータ個数まで対応

/*テキストファイルの読み込み*/
unsigned int readdata(char sounddata[])
{
 unsigned int n=0 ;//入力データの個数

 while(scanf("%d",&sounddata[n++])!=EOF)
	 if(n>=MAX){
		 fprintf(stderr,"警告：入力データ数が最大値に達しました\n") ;
		 break ;
	}
 return n-1 ;
}

/*4バイトのデータをバイナリで出力*/
void putword(int w,FILE *fp)
{
 fwrite(&w,sizeof(int),1,fp) ;
} 

/*wavファイルヘッダの作成*/
void makeheader(unsigned int slength,FILE *fp)
{
 fprintf(fp,"RIFF") ;//RIFF
 putword(slength+36,fp) ;//ファイルサイズ-8(=36+データ長)
 fprintf(fp,"WAVE") ;//WAVEファイル
 fprintf(fp,"fmt ") ;//fmtチャンクの開始
 putword(16,fp) ;//fmtチャンク長(16byte)
 putc(1,fp);putc(0,fp);//フォーマットＩＤ
 putc(1,fp);putc(0,fp);//チャンネル数（モノラル）
 putword(8000,fp) ;//サンプリングレート（8000Hz)
 putword(8000,fp) ;//データ速度（8000Hz)
 putc(1,fp);putc(0,fp);//ブロックサイズ
 putc(8,fp);putc(0,fp);//bits/sample
 fprintf(fp,"data") ;//dataチャンク
 putword(slength,fp) ;//波形データのバイト数
}


int main(int argc,char **argv)
{
 char sounddata[MAX] ;//音データ
 unsigned int slength ;
 FILE *fp ;

 if(argc!=2){//ファイル名が指定されていない
  fprintf(stderr,"使い方　makewav 出力ファイル名\n");
  exit(1) ;
 }
 if((fp=fopen(argv[1],"wb"))==NULL){//ファイルが開けない
  fprintf(stderr,"エラー　ファイル%sをオープンできません\n",argv[1]);
  exit(1) ;
 }
 
 /*数値（テキスト）の読み込み*/
 slength=readdata(sounddata) ;
 
 /*ヘッダ情報の出力*/
 makeheader(slength,fp) ;
 /*データの出力*/
 fwrite(sounddata,sizeof(char),slength,fp) ;
 return 0 ;
}
