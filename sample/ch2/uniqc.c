//	uniqc.c
//	重複行の数え上げと削除
//	同じ行の繰り返しを削除します

#include<stdio.h>
#include<string.h>
#define MAXLINE 65535 //1行64kバイトまで処理可能

int main()
{
 char new[MAXLINE] ;//入力行
 char old[MAXLINE] ;//前の行
 int count=1 ;//重複回数の数え上げ

 /*テキストを読み込む*/
 fgets(old,MAXLINE,stdin) ;
 while(fgets(new,MAXLINE,stdin)!=NULL){
  if(strcmp(new,old)==0) ++count ;//等しい行
  else{//異なる行
   printf("%d\t%s",count,old);
   count=1 ;
   strcpy(old,new) ;
  }
 }
 printf("%d\t%s",count,old);

 return 0;
}

