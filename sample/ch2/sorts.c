//	sorts.c
//	文字列を整列します
//  n-gram整列用ですから，1行は16byte以内に制限しています

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LINESIZE 16 //1行16バイトまで処理可能
#define MAX 65536*3 //192k行まで処理可能  

char lines[MAX][LINESIZE] ; //整列対象

int main()
{
 char buf[LINESIZE] ;//読み込みバッファ
 int pos=0 ;//読み込み行数のカウンタ
 int i ;
 
 /*テキストを読み込む*/
 while(fgets(buf,LINESIZE,stdin)!=NULL){
   strcpy(lines[pos],buf) ;
   if((++pos)>=MAX){ fprintf(stderr,"File too big.\n") ;exit(1);}
  }
 /*整列*/
 qsort(lines,pos,LINESIZE,(int (*)(const void *,const void *))strcmp) ;
 /*出力*/
 for(i=0;i<pos;++i)
  printf("%s",lines[i]) ;
  
 return 0;
}
