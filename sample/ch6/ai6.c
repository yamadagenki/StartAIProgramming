//	ai6.c
//      �w�K�ɂ���b�𑝂₷�l�H���\�v���O����
//	���ɂȂ�̂́C�`�ԑf�̘A���ɂ�蕶���쐬����l�H���\�v���O����ai3.c
// ����сC�`�ԑf�؂�o���v���O����cutm_p.c�v���O�����ł�
//	�`�ԑf�̘A�����i�[���ꂽ�t�@�C��morph.txt��p���܂�
// ���炩���ߏ�������`�ԑf�̐؂�o���ɂ�cutm_p.c�v���O�������g���Ă��������D

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
 /* ai3.c����̕ύX�_*/
 fclose(fp) ;//�t�@�C�������
 /* �ύX�_�����*/
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

/* �ȉ��Cai3.c����̕ύX�_*/
/*�ȉ���cutm_p.c�v���O��������̊֐��̒ǉ�*/
/*�J�^�J�i������ȊO���̔���*/
int iskatakana(char ch1,char ch2)
{
 int d1,d2 ;
 d1=(unsigned char)ch1 ;
 d2=(unsigned char)ch2 ;
 if((d1==0x83)&&(d2>=40)&&(d2<=0x96)) return 1 ;
 else return 0 ;
}
/*����̐ݒ�*/
int typeset(char ch1,char ch2)
{
 if(iskanji(ch1)) return 0 ;//�����͂O
 else if(iskatakana(ch1,ch2)) return 1 ;//�J�^�J�i�͂P
 else return 2 ;//���̑��͂Q
}
/*��Ǔ_�̌��o*/
int ispunct(char *ch)
{
 if((strncmp(ch,"�D",2)==0)
  ||(strncmp(ch,"�B",2)==0)
  ||(strncmp(ch,"�C",2)==0)
  ||(strncmp(ch,"�A",2)==0)
  ) return 1;//��Ǔ_�Ȃ�P
  else return 0 ;
}
/*�S�p�����̂ݎ��o��*/
void getwidechar(char *t,char *s,int n)
{
 int in=0;//���̓f�[�^�̃|�C���^
 int out=0 ;//�o�̓f�[�^�̃|�C���^
 int d;
 while(in<n){
  d=(unsigned char)s[in] ;
  if(((d>0x7F)&&(d<0xA0))||(d>0xDF)&&(d<0xF0)){//�Q�o�C�g����
    t[out++]=s[in++];
    t[out++]=s[in++];
  }
  else ++in ;
 }
 t[out]='\0' ;//������̏I�[
}
/*�����܂ł�cutm_p.c�v���O�����̊֐��̒ǉ�*/

/*�`�ԑf�̐؂�o��*/
/*���̊֐��́Ccutm_p.c�v���O�����̓����̊֐��������������̂ł�*/
void outputmorph(char *target,FILE *fp) 
{
 int i=0 ;
 int now,last;//����(0)�E�J�^�J�i(1)�E���̑�(2)�̕�
 last=typeset(target[i],target[i+1]) ;
 while((target[i]!='\0')&& (i<MAXLINE)){
  if(ispunct(&(target[i]))==0){//��Ǔ_�ł͂Ȃ�
   /*�����̏���*/
   now=typeset(target[i],target[i+1]) ;
   if(now!=last) {//���킪�ς���Ă���
    putc('\n',fp) ;//��؂�̉��s���o��
    last=now ;
   }
   putc(target[i++],fp) ;
   putc(target[i++],fp) ;
  }
  else{//��Ǔ_
  /*�����Ȃǂ̏���*/
   putc('\n',fp) ;//��؂�̉��s���o��
   putc(target[i++],fp) ;
   putc(target[i++],fp) ;
   putc('\n',fp) ;//��؂�̉��s���o��
   last=typeset(target[i],target[i+1]) ;   
  } 
 }
}

/*���p�҂̓��͂���`�ԑf�t�@�C�����X�V����*/
void addmorph(char line[])
{
 FILE *fp;
 char target[MAXLINE];

 if((fp=fopen(FILENAME,"a"))==NULL){
  fprintf(stderr,"�G���[�@�t�@�C��morph.txt�̃I�[�v���Ɏ��s���܂���\n");
  exit(1) ;
 }
 /*�S�p�����̂ݎ��o��*/
 getwidechar(target,line,strlen(line)) ;
 outputmorph(target,fp);//�`�ԑf�̒ǉ�
 fclose(fp) ;
}
/*�ȏ�ŁCai3.c�v���O��������̕ύX�_�I���*/
 
int main()
{
 char line[MAXLINE] ;//���̓o�b�t�@
 char db[MAXNO][2][MAXLINE] ;//�`�ԑf�̃f�[�^�x�[�X
 int n ;//�`�ԑf�̌�
 char startch[MAXLINE];//�J�n����
 
 /*�����̏�����*/
 srand(65535) ;

 /*�I�[�v�j���O���b�Z�[�W*/
 printf("������F���b�Z�[�W���ǂ���\n");
 printf("���Ȃ��F");
 /*��b���܂��傤*/
 while(fgets(line,MAXLINE-1,stdin)!=NULL){
	 /* ai3.c����̕ύX�_*/
	 addmorph(line) ;//���p�҂̓��͂ɂ��`�ԑf�t�@�C�����X�V����
  /*�`�ԑf�t�@�C���̓ǂݍ���*/
  n=readmorph(db) ;
  /*�ύX�_�I���*/
  printf("������F");
  setstartch(startch,line) ;
  generates(startch,db,n) ;
  printf("���Ȃ��F");
 }
 /*�G���f�B���O���b�Z�[�W*/
 printf("������F�΂��΁`��\n");
 return 0 ;
}



