//	genbymorph.c
//	�`�ԑf��̓v���O����cputm_p.c�̏o�͂����`�ԑf�̘A���ɂ�蕶���쐬����
//	�`�ԑf�̘A�����i�[���ꂽ�t�@�C��morph.txt��p���܂�
//	�J�n��������w�肷��ƕ��𐶐����܂�

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXNO 10000 //�`�ԑf�A���̍ő吔
#define MAXLINE 48 //1�s�̍ő�o�C�g��
#define FILENAME "morph.txt" //�`�ԑf���i�[���ꂽ�t�@�C��


/*�`�ԑf�t�@�C���̓ǂݍ���*/
int readmorph(char db[MAXNO][2][MAXLINE])
{
 FILE *fp;
 char line[MAXLINE] ,oldline[MAXLINE];
 int i=0 ;

 if((fp=fopen(FILENAME,"r"))==NULL){
  fprintf(stderr,"�G���[�@�t�@�C��morph.txt������܂���\n");
  exit(1) ;
 }
 fgets(oldline,MAXLINE,fp) ;
 if(strchr(oldline,'\n')!=NULL)*strchr(oldline,'\n')='\0' ;//���s�R�[�h����菜��
 while(fgets(line,MAXLINE,fp)!=NULL){
  if(strchr(line,'\n')!=NULL) *strchr(line,'\n')='\0' ;//���s�R�[�h����菜��
  strncpy(db[i][0],oldline,MAXLINE) ;//�`�ԑf���R�s�[
  strncpy(db[i][1],line,MAXLINE) ;//�`�ԑf���R�s�[
  strncpy(oldline,line,MAXLINE) ;
  printf("DEBUG %s %s\n",db[i][0],db[i][1]) ;
  ++i ;
  if(i>=MAXNO){
   fprintf(stderr,"�x���@�`�ԑf����%d�ɐ������܂�\n",MAXNO);
   break ;
  }
 }
 return i ;//�`�ԑf�̌���Ԃ�
}
/*�J�n����������܂܂�邩������*/
int findch(char *startch,char db[MAXNO][2][MAXLINE],int n) 
{
 int i ;
 int no=0 ;
 for(i=0;i<n;++i){
  if(strncmp(startch,db[i][0],MAXLINE)==0) ++ no ;
 }
 return no ;
}
/*num�ȉ��̗������Z�b�g*/
int setrnd(int num)
{
 int rndno ;
 while((rndno=(double)rand()/RAND_MAX*num)==num) ;
 return rndno ;

}

/*���̕������`�ԑf�cB�ɂ�胉���_���ɃZ�b�g*/
void setrndstr(char *startch,char db[MAXNO][2][MAXLINE],int n)
{
  strncpy(startch,db[setrnd(n)][1],MAXLINE);
}

/*���̕������`�ԑf�c�a�ɂ��Z�b�g*/
void setnext(char *startch,char db[MAXNO][2][MAXLINE],int n,int num) 
{
 int i ;
 int no=-1 ;
 int point ;
 
 point=setrnd(num) ;//num�ȉ��̗������Z�b�g
 for(i=0;i<n;++i){
  if(strncmp(startch,db[i][0],MAXLINE)==0) ++ no ;
  if(no==point){
   strncpy(startch,db[i][1],MAXLINE);
  break ;
  }
 }  
}


/*���̐���*/
void generates(char *startch,char db[MAXNO][2][MAXLINE],int n)
{
 int i,num ;

 /*�J�n������̏o��*/
 printf("%s",startch) ;
  /*��_���o��܂ŌJ��Ԃ�*/
 do{
  /*�J�n����������܂܂�邩������*/
  num=findch(startch,db,n) ;
  /*���̒����烉���_���ɕ������I��*/
  if(num!=0)
    setnext(startch,db,n,num) ;
  else
    setrndstr(startch,db,n) ;
  /*�������o�͂���*/
  printf("%s",startch) ;
 }while((strncmp(startch,"�D",2)!=0)&&(strncmp(startch,"�B",2)!=0)) ;
 printf("\n") ;
}

int main()
{
 char db[MAXNO][2][MAXLINE] ;//�`�ԑf�̃f�[�^�x�[�X
 int n ;//�`�ԑf�̌�
 char startch[MAXLINE];//�J�n����
 int i ;
 char workch[MAXLINE];//��Ɨp�̕���

 
 /*�����̏�����*/
 srand(65535) ;
 /*�`�ԑf�t�@�C���̓ǂݍ���*/
 n=readmorph(db) ;


 /*�J�n�����̌���*/
 printf("�J�n���������͂��Ă�������\n") ;
 fgets(startch,MAXLINE,stdin) ;
 if(strchr(startch,'\n')!=NULL) *strchr(startch,'\n')='\0' ;//���s�R�[�h����菜��

 /*10��̕��̐���*/
 for(i=0;i<10;++i){
    strcpy(workch,startch) ;
    generates(workch,db,n) ;
 }
 return 0 ;
}



