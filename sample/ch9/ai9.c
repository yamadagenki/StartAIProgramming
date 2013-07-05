// ai9.c
//   �������ӎ����C����ɑΘb��i�߂�l�H���\�v���O����
//   ���s�ɂ́C�`�ԑf�A�����i�[�����t�@�C��morph.txt���K�v�ł��D

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXNO 10000 //�`�ԑf�A���̍ő吔
#define MAXLINE 48 //1�s�̍ő�o�C�g���i�`�ԑf�t�@�C���j
#define LINENUM 512 //1�s�̍ő�o�C�g���i�����������j
#define FILENAME "morph.txt" //�`�ԑf���i�[���ꂽ�t�@�C��
#define LIMITLENGTH 4 //�������̊J�n�����̍Œᒷ
#define LIMITNO 20 //�Θb�̌J��Ԃ���

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
 fclose(fp) ;//�t�@�C�������
 
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
void generates(char *startch,char db[MAXNO][2][MAXLINE],int n,char *line)
{
 int i,num ;

 /*�J�n������̏o��*/
 printf("%s",startch) ;
 strncat(line,startch,MAXLINE) ;//���⎩���̂��߂̕ۑ�
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
  strncat(line,startch,LINENUM) ;//���⎩���̂��߂̕ۑ�
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


/*�`�ԑf�̐؂�o��*/
void outputmorph(char *target,FILE *fp) 
{
 int i=0 ;
 int now,last;//����(0)�E�J�^�J�i(1)�E���̑�(2)�̕�
 last=typeset(target[i],target[i+1]) ;
 while((target[i]!='\0')&& (i<LINENUM)){
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
 char target[LINENUM];

 if((fp=fopen(FILENAME,"a"))==NULL){
  fprintf(stderr,"�G���[�@�t�@�C��morph.txt�̃I�[�v���Ɏ��s���܂���\n");
  exit(1) ;
 }
 /*�S�p�����̂ݎ��o��*/
 getwidechar(target,line,strlen(line)) ;
 outputmorph(target,fp);//�`�ԑf�̒ǉ�
 fclose(fp) ;
}

 /* �J�n������̌���*/
void setstartch(char *startch,char *newline)
{
 int i=0,j=0;
 int count=0 ;//���͕����̌`�ԑf�̐�
 char target[LINENUM] ;//�S�p�������������o�������͕�
 char line[LINENUM] ;//�����Ώۂ̕��i�O��܂��͑O�X��̕��j
 int now,last ;
 int startpoint ;
 static char oldline[LINENUM]="���͐l�H���\�ł��D" ;

 /*�ԓ��̑ΏۂƂ��镶�̑I���i�O��܂��͑O�X��j*/
 if(setrnd(5)<4) strncpy(line,newline,LINENUM) ;//�O��̕�
   /*ai8.c�Ɣ�r����ƁC�O��̕���O�X��̕������d�v������䗦������*/
 else strncpy(line,oldline,LINENUM) ;//�O�X��̕�

 /*�S�p�����̐؂�o��*/
 getwidechar(target,line,strlen(line)) ;

 /*�`�ԑf�̌��̃J�E���g*/
 last=typeset(target[i],target[i+1]) ;
 while((target[i]!='\0')&& (i<LINENUM)){
   now=typeset(target[i],target[i+1]) ;
   if(now!=last) {//���킪�ς���Ă���
    ++count ;//�`�ԑf�̐����グ
    last=now ;
   } 
   ++i;++i;
 }
 /*�J�n������ƂȂ�`�ԑf�̌���*/
 startpoint=setrnd(count+1) ;

 /*�J�n������̌���*/
 count=0 ;i=0;//���Z�b�g
 last=typeset(target[i],target[i+1]) ;
 while((target[i]!='\0')&& (i<LINENUM)){
   now=typeset(target[i],target[i+1]) ;
   if(now!=last) {//���킪�ς���Ă���
    ++count ;//�`�ԑf�̐����グ
    last=now ;
   } 
   if(count>=startpoint) break ;
   ++i;++i;
 }
 /*�`�ԑf�̃R�s�[*/
 while((target[i]!='\0')&& (i<LINENUM)){
   now=typeset(target[i],target[i+1]) ;
   if((now!=last)||(ispunct(&target[i])))  break ;
   startch[j++]=target[i++];
   startch[j++]=target[i++];
 }
 if(strlen(startch)<LIMITLENGTH) strncpy(startch,"�l�H�m�\",LINENUM);//�Z������ꍇ
 strncpy(oldline,newline,LINENUM) ;//1��O�̕���ۑ����Ă���
}


int main()
{
 char line[LINENUM] ;//���̓o�b�t�@
 char db[MAXNO][2][MAXLINE] ;//�`�ԑf�̃f�[�^�x�[�X
 int n ;//�`�ԑf�̌�
 char startch[MAXLINE];//�J�n����
 int i ;//�J��Ԃ��̐���
 
 /*������*/
 srand(32768) ;
 strncpy(line,"�l�H���\��l�H�l�i�ɏ��؂����悤�D",LINENUM) ;

 /*��b���܂��傤*/
 for(i=0;i<LIMITNO;++i){
  addmorph(line) ;//�`�ԑf�t�@�C�����X�V����
  /*�`�ԑf�t�@�C���̓ǂݍ���*/
  n=readmorph(db) ;
  printf("������F");
  setstartch(startch,line) ;
  strncpy(line,"",LINENUM) ;
  generates(startch,db,n,line) ;
 }
 /*�G���f�B���O���b�Z�[�W*/
 printf("������F�΂��΁`��\n");
 return 0 ;
}



