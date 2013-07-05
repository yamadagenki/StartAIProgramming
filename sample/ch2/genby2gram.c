//	genby2gram.c
//	2-gram�̘A���ɂ�蕶���쐬����
//	2-gram���i�[���ꂽ�t�@�C��2gram.txt��p���܂�
//	�J�n�������w�肷��ƕ��𐶐����܂�

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXNO 100000 //2-gram�̍ő吔
#define MAXLINE 256 //1�s�̍ő�o�C�g��
#define FILENAME "2gram.txt" //2-gram���i�[���ꂽ�t�@�C��

/*2-gram�t�@�C���̓ǂݍ���*/
int read2gram(char db2gram[MAXNO][6])
{
 FILE *fp;
 char line[MAXLINE] ;
 int i=0 ;

 if((fp=fopen(FILENAME,"r"))==NULL){
  fprintf(stderr,"�G���[�@�t�@�C��2gram.txt������܂���\n");
  exit(1) ;
 }

 while(fgets(line,MAXLINE,fp)!=NULL){
  strncpy(db2gram[i],line,4) ;//�S�p2�������R�s�[
  db2gram[i][5]='\0' ;
  ++i ;
 }
 return i ;//2-gram�̌���Ԃ�
}
/*�J�n����������܂܂�邩������*/
int findch(char *startch,char db2gram[MAXNO][6],int n) 
{
 int i ;
 int no=0 ;
 for(i=0;i<n;++i){
  if(strncmp(startch,db2gram[i],2)==0) ++ no ;
 }
 return no ;
}
/*num�����̗������Z�b�g*/
int setrnd(int num)
{
 int rndno ;
 while((rndno=(double)rand()/RAND_MAX*num)==num) ;
 return rndno ;

}

/*���̕�����n-gram�ɂ�胉���_���ɃZ�b�g*/
void setrndstr(char *startch,char db2gram[MAXNO][6],int n)
{
 int i ;
 int point ;
 
 point=setrnd(n) ;//n�����̗������Z�b�g
 for(i=0;i<n;++i){
  if(i==point){
   startch[0]=db2gram[i][2] ;
   startch[1]=db2gram[i][3] ;
   startch[2]='\0' ;
   break ;
  }
 }  
}

/*���̕�����n-gram�ɂ��Z�b�g*/
void setnext(char *startch,char db2gram[MAXNO][6],int n,int num) 
{
 int i ;
 int no=0 ;
 int point ;
 
 point=setrnd(num) ;//num�����̗������Z�b�g
 for(i=0;i<n;++i){
  if(strncmp(startch,db2gram[i],2)==0) ++ no ;
  if(no==point){
   startch[0]=db2gram[i][2] ;
   startch[1]=db2gram[i][3] ;
   startch[2]='\0' ;
   break ;
  }
 }  
}


/*���̐���*/
void generates(char *startch,char db2gram[MAXNO][6],int n)
{
 int i,num ;
 
  /*�J�n�������o�͂���*/
  putchar(startch[0]) ; putchar(startch[1]) ;
  /*��_���o��܂ŌJ��Ԃ�*/
 do{
  /*�J�n����������܂܂�邩������*/
  num=findch(startch,db2gram,n) ;
  /*���̒����烉���_���ɕ������I��*/
  if(num!=0)
   setnext(startch,db2gram,n,num) ;
  else
   setrndstr(startch,db2gram,n) ;
  /*�������o�͂���*/
  putchar(startch[0]) ; putchar(startch[1]) ;
 }while((strncmp(startch,"�D",2)!=0)&&(strncmp(startch,"�B",2)!=0)) ;
 printf("\n") ;
}

 



int main()
{
 char db2gram[MAXNO][6] ;//2gram�̃f�[�^�x�[�X
 int n ;//2-gram�̌�
 char startch[MAXLINE];//�J�n����
 int i ;
 char workch[MAXLINE];//��Ɨp�̕���

 
 /*�����̏�����*/
 srand(65535) ;
 /*2-gram�t�@�C���̓ǂݍ���*/
 n=read2gram(db2gram) ;


 /*�J�n�����̌���*/
 printf("�J�n��������͂��Ă�������\n") ;
 fgets(startch,MAXLINE,stdin) ;

 /*10��̕��̐���*/
 for(i=0;i<10;++i){
  strcpy(workch,startch) ;
  generates(workch,db2gram,n) ;
 }
 return 0 ;
}



