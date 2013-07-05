//	cutkk.c
//	������J�^�J�i��̒��o
//	�e�L�X�g�f�[�^����C������J�^�J�i�ɂ���𒊏o���܂�

#include<stdio.h>
#include<string.h>
#define MAX 65535*3 //192k�o�C�g�܂ŏ����\

/*�e�L�X�g��ǂݍ���*/
int getsource(char *s)
{
 int n=0 ;//�������̃J�E���^

 while((s[n++]=getchar())!=EOF) ;
 return n ;
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
 char w[3] ;
 w[0]=ch1; w[1]=ch2; w[2]='\0' ;
 d1=(unsigned char)ch1 ;
 d2=(unsigned char)ch2 ;
 if((d1==0x83)&&(d2>=40)&&(d2<=0x96)) return 1 ;
 if(strncmp(w,"�[",2)==0) return 1 ;//�����L���������ʈ���
 else return 0 ;
}
/*����̐ݒ�*/
int typeset(char ch1,char ch2)
{
 if(iskanji(ch1)) return 0 ;//�����͂O
 else if(iskatakana(ch1,ch2)) return 1 ;//�J�^�J�i�͂P
 else return 2 ;//���̑��͂Q
}


/*��̐؂�o��*/
void outputmorph(char *target) 
{
 int i=0 ;
 int now,last;//����(0)�E�J�^�J�i(1)�E���̑�(2)�̕�
 last=typeset(target[i],target[i+1]) ;
 while(target[i]!='\0'){
   now=typeset(target[i],target[i+1]) ;
   if((now==0)||(now==1)){//�������J�^�J�i
    putchar(target[i++]) ;
    putchar(target[i++]) ;
   }
   else i+=2 ;//�����E�J�^�J�i�ȊO�̓ǂݔ�΂�
   if((now!=last)&&(last!=2)) {//���킪�ς���Ă���
    putchar('\n') ;//��؂�̉��s���o��
   }
   last=now ;
 }
}

int main()
{
 char source[MAX] ;//���̓f�[�^
 char target[MAX] ;//�S�p�f�[�^
 int numchar ;//���͕�����

 /*�e�L�X�g��ǂݍ���*/
 numchar=getsource(source) ;

 /*�S�p�����̂ݎ��o��*/
 getwidechar(target,source,numchar) ;

 /*��̐؂�o��*/
 outputmorph(target) ;

 return 0 ;
}

