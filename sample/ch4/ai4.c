//	しゃべる人工無能プログラム　ai4.c
//	このプログラムは，音声で返答する人工無能です
//	ただし，返答内容は固定です
// 返答を記録したwavファイル（fuun.wav,sounano.wav,soukamo.wav)とspeec.exeが必要です
#include<stdio.h>
#include<stdlib.h>
#define MAXLINE 256

/*num未満の乱数をセット*/
int setrnd(int num)
{
 int rndno ;
 while((rndno=(double)rand()/RAND_MAX*num)==num) ;
 return rndno ;
}

/*人工無能の返答作成（ランダム）*/
void reply(void)
{
	int rndval ;
	rndval=setrnd(4) ;
 if(rndval==0){
  system("type fuun.wav > out.wav");
  printf("さくら：ふ～ん，それで？\n") ;
 }
 else if(rndval==1){
  system("type sounano.wav > out.wav");
  printf("さくら：そうなの？\n") ;
 }
 else {
  system("type soukamo.wav >out.wav");
  printf("さくら：そうかもしれないわね・・・\n") ;
 }
 system("speech") ;
}

int main()
{
 char line[MAXLINE] ;//入力バッファ

 /*オープニングメッセージ*/
 printf("さくら：メッセージをどうぞ\n");
 printf("あなた：");
 /*会話しましょう*/
 while(fgets(line,MAXLINE,stdin)!=NULL){
  reply() ;//人工無能の返答
  printf("あなた：");
 }
 /*エンディングメッセージ*/
 printf("さくら：ばいば～い\n");
 system("type byebye.wav >out.wav");
 system("speech") ;
 return 0 ;
}
