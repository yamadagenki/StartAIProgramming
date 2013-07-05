//	gens2.c
//	書き換え規則による文の生成プログラムその2
//	書き換え規則Bに従って文を生成します
//  書き換え規則B
//		規則①	<文>→<名詞句＞＜動詞句＞
//　　　規則②	<名詞句>→＜形容詞句＞＜名詞＞は
//　　　規則③	<名詞句>→＜名詞＞は
//　　　規則④	<動詞句>→＜動詞＞
//　　　規則⑤	<動詞句>→＜形容詞＞
//　　　規則⑥	<動詞句>→＜形容動詞＞
//　　　規則⑦	<形容詞句>→＜形容詞＞＜形容詞句＞
//　　　規則⑧	<形容詞句>→＜形容詞＞




#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define NMAX 8192 //終端記号項目数の上限
#define CHMAX 32  //終端記号の長さの上限
#define NFILE "noun.txt"//名詞の格納されたファイル
#define VFILE "verb.txt"//動詞の格納されたファイル
#define AFILE "adj.txt"//形容詞の格納されたファイル
#define DFILE "adjv.txt"//形容動詞の格納されたファイル

char nlist[NMAX][CHMAX]; int nnum;
char vlist[NMAX][CHMAX]; int vnum;
char alist[NMAX][CHMAX]; int anum;
char dlist[NMAX][CHMAX]; int dnum;

void ap(void) ;
void np(void) ;
void vp(void) ;
void sentence(void) ;
int setrnd(int num) ;

/*規則④<動詞句>→<動詞> ⑤<動詞句>→<形容詞> ⑥<動詞句>→<形容動詞>*/
void vp()
{
 int r ;
 r=setrnd(3) ;
 if(r==2){//規則④
  printf("%s",vlist[setrnd(vnum)]) ;
 }
 else if(r==1){//規則⑤
  printf("%s",alist[setrnd(anum)]) ;
 }
 else{//規則⑥
  printf("%s",dlist[setrnd(dnum)]) ;
 }
}

/*規則⑦<形容詞句>→＜形容詞＞＜形容詞句＞ ⑧<形容詞句>→＜形容詞＞*/
void ap()
{
 if(setrnd(2)>0){//規則⑦
  ap() ;
  printf("%s",alist[setrnd(vnum)]) ;
 }
 else{//規則⑧
  printf("%s",alist[setrnd(vnum)]) ;
 }
}

/*規則②<名詞句>→＜形容詞句＞＜名詞＞は　規則③　<名詞句>→＜名詞＞は*/
void np()
{
 if(setrnd(2)>0){//規則②
  ap() ;
  printf("%sは",nlist[setrnd(nnum)]) ;
 }
 else{//規則③
  printf("%sは",nlist[setrnd(nnum)]) ;
 } 
}

/*規則①	<文>→<名詞句＞＜動詞句＞*/
void sentence()
{
 np() ;//名詞句の生成
 vp() ;//動詞句の生成
}

/*終端記号リストの読み込み*/
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
 int i ;
 
 /*乱数の初期化*/
 srand(65535) ;
 /*終端記号リストの読み込み*/
 nnum=setlist(nlist,NFILE) ;
 vnum=setlist(vlist,VFILE) ;
 anum=setlist(alist,AFILE) ;
 dnum=setlist(dlist,DFILE) ;

 for(i=0;i<50;++i){
  /*文の生成*/
  sentence() ;
  printf("．\n") ;
}
 return 0 ;
}



