//	gens1.c
//	書き換え規則による文の生成プログラムその１
//	書き換え規則Aに従って文を生成します
//  書き換え規則　A
//    規則①	<文>→<名詞句＞＜動詞句＞
//  　規則②	<名詞句>→＜名詞＞は
//　　規則③　 <動詞句>→＜動詞＞


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define NMAX 8192 //終端記号項目数の上限
#define CHMAX 32  //終端記号の長さの上限
#define NFILE "noun.txt"//名詞の格納されたファイル
#define VFILE "verb.txt"//動詞の格納されたファイル

void np(char nlist[NMAX][CHMAX],int nnum) ;
void vp(char vlist[NMAX][CHMAX],int vnum) ;
void sentence(char nlist[NMAX][CHMAX],int nnum,char vlist[NMAX][CHMAX],int vnum) ;
int setrnd(int num) ;

/*規則③　<動詞句>→＜動詞＞*/
void vp(char vlist[NMAX][CHMAX],int vnum)
{
 printf("%s",vlist[setrnd(vnum)]) ;
 
}

/*規則②		<名詞句>→＜名詞＞は*/
void np(char nlist[NMAX][CHMAX],int nnum)
{
 printf("%sは",nlist[setrnd(nnum)]) ;
 
}

/*規則①	<文>→<名詞句＞＜動詞句＞*/
void sentence(char nlist[NMAX][CHMAX],int nnum,char vlist[NMAX][CHMAX],int vnum)
{
 np(nlist,nnum) ;//名詞句の生成
 vp(vlist,vnum) ;//動詞句の生成
}

/*名詞リスト・動詞リストの読み込み*/
int setlist(char list[NMAX][CHMAX],char *filename)
{
 FILE *fp;
 char line[CHMAX] ;
 int i=0 ;

 if((fp=fopen(filename,"r"))==NULL){
  fprintf(stderr,"エラー　ファイル%sがありません\n",filename);
  exit(1) ;
 }

 while(fgets(line,CHMAX,fp)!=NULL){
  strncpy(list[i],line,CHMAX) ;
  list[i][strlen(line)-1]='\0' ;
  ++i ;
 }
 fclose(fp) ;
 return i ;//入力個数を返す
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
 char nlist[NMAX][CHMAX] ;//名詞リスト
 char vlist[NMAX][CHMAX] ;//動詞リスト
 int nnum,vnum ;//リストの項目数
 int i ;
 
 /*乱数の初期化*/
 srand(65535) ;
 /*名詞リストと動詞リストの読み込み*/
 nnum=setlist(nlist,NFILE) ;
 vnum=setlist(vlist,VFILE) ;

 for(i=0;i<50;++i){
  /*文の生成*/
  sentence(nlist,nnum,vlist,vnum) ;
  printf("．\n") ;
}
 return 0 ;
}



