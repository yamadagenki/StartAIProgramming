//	ai3.c
//	�`�ԑf�̘A���ɂ�蕶���쐬����l�H���\�v���O�����ł�
//	�`�ԑf�̘A�����i�[���ꂽ�t�@�C��morph.txt��p���܂�
// �`�ԑf�̐؂�o���ɂ�cutm_p.c�v���O�������g���Ă��������D

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

/*����������ȊO���̔���*/
int iskanji(char ch)
{
 int d ;
 d=(unsigned char)ch ;
 if(d>=0x88) return 1 ;
 else return 0 ;
}

/* �J�n������̌���*/
void setstartch(char *startch,char *line)
{
 unsigned int i,j;
 
 /*�����ȊO�̓ǂݔ�΂�*/
 for(i=0;i<strlen(line);i+=2)
  if(iskanji(line[i])==1) break ;
 if(i==strlen(line)){//������������Ȃ�
  strncpy(startch,"�l�H�m�\",MAXLINE) ;
 }
 else{
 /*�����̒��o*/
 j=0 ;
 while((iskanji(line[i])==1)&&(line[i]!='\0')){
  startch[j++]=line[i++] ;
  startch[j++]=line[i++] ;
 }
 startch[j]='\0' ;
 }
}


int main()
{
 char line[MAXLINE] ;//���̓o�b�t�@
 char db[MAXNO][2][MAXLINE] ;//�`�ԑf�̃f�[�^�x�[�X
 int n ;//�`�ԑf�̌�
 char startch[MAXLINE];//�J�n����
 
 /*�����̏�����*/
 srand(65535) ;
 /*�`�ԑf�t�@�C���̓ǂݍ���*/
 n=readmorph(db) ;

 /*�I�[�v�j���O���b�Z�[�W*/
 printf("������F���b�Z�[�W���ǂ���\n");
 printf("���Ȃ��F");
 /*��b���܂��傤*/
 while(fgets(line,MAXLINE,stdin)!=NULL){
  printf("������F");
  setstartch(startch,line) ;
  generates(startch,db,n) ;
  printf("���Ȃ��F");
 }
 /*�G���f�B���O���b�Z�[�W*/
 printf("������F�΂��΁`��\n");
 return 0 ;
}



