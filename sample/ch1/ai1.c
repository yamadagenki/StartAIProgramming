//	初めての人工無能プログラム　ai1.c
//	このプログラムは，常に決まった返答を返す人工無能です
//	本当に無能ですね

#include<stdio.h>
#define MAXLINE 256
int main()
{
 char line[MAXLINE] ;//入力バッファ

 /*オープニングメッセージ*/
 printf("さくら：メッセージをどうぞ\n");
 printf("あなた：");
 /*会話しましょう*/
 while(fgets(line,MAXLINE,stdin)!=NULL){
  printf("さくら：ふ～ん，それで？\n");
  printf("あなた：");
 }
 /*エンディングメッセージ*/
 printf("さくら：ばいば～い\n");
 return 0 ;
}
