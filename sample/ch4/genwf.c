//	genwf.c
//	天気予報を”しゃべる”プログラム
//	書き換え規則Ｃに従って天気予報を生成します
//  書き換え規則Ｃ
//	規則①	<文>→<地区＞＜時間帯＞＜天気＞
// 規則②	<地区>→東京地方
// 規則③	<地区>→福井県
// 規則④	<時間帯>→今日は
// 規則⑤	<時間帯>→明日は
// 規則⑥	<天気>→＜天気＞ところにより＜天気＞
// 規則⑦	<天気>→晴れ
// 規則⑧	<天気>→曇り
// 規則⑨	<天気>→雨
// 実行には，テキスト形式で音声データを格納した以下の8つのファイルが必要です．
// toukyouchihou.txt fukuiken.txt
// kyouha.txt asuha.txt
// hare.txt kumori.txt ame.txt
// tokoroniyori.txt



#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void weather(void) ;
void timezone(void) ;
void region(void) ;
void sentence(void) ;
int setrnd(int num) ;

/*規則⑥	<天気>→＜天気＞ところにより＜天気＞*/
/*規則⑦	<天気>→晴れ 規則⑧	<天気>→曇り  規則⑨	<天気>→雨*/
void weather()
{
	int rndval ;
	rndval=setrnd(4) ;
 if(rndval==0){//規則⑥
  weather() ;
  system("type tokoroniyori.txt >> out.txt");
  printf("ところにより") ;
  weather() ;
 }
 else if(rndval==1){//規則⑦
  system("type hare.txt >> out.txt");
  printf("晴れ") ;
 }
 else if(rndval==2){//規則⑧
  system("type kumori.txt >> out.txt");
  printf("曇り") ;
 }
 else {//規則⑨
  system("type ame.txt >> out.txt");
  printf("雨") ;
 } 
}


/*規則④	<時間帯>→今日は   規則⑤	<時間帯>→明日は*/
void timezone()
{
 if(setrnd(2)>0){//規則④
  system("type kyouha.txt >> out.txt");
  printf("今日は") ;
 }
 else{//規則1⑤
  system("type asuha.txt >> out.txt");
  printf("明日は") ;
 } 
}

/*規則②<地区>→東京地方　規則③　<地区>→福井県*/
void region()
{
 if(setrnd(2)>0){//規則②
  system("type toukyouchihou.txt > out.txt");
  printf("東京地方") ;
 }
 else{//規則③
  system("type fukuiken.txt > out.txt");
  printf("福井県") ;
 } 
}

/*規則①	<文>→<地区＞＜時間帯＞＜天気＞*/
void sentence()
{
 region() ;//地区の生成
 timezone() ;//時間帯の生成
 weather();//天気の生成
}

/*num未満の乱数をセット*/
int setrnd(int num)
{
 int rndno ;
 while((rndno=(double)rand()/RAND_MAX*num)==num) ;
 return rndno ;
}

int main()
{
 char ans ;
 
 /*乱数の初期化*/
 srand(65535) ;

 /*文の生成*/
 while(1){
  sentence() ;
  printf("\n") ;
  printf("これで良いですか？(y/n)\n") ;
  scanf("%c",&ans) ;
  if(ans=='y') break ;
}

 return 0 ;
}



