//	make3gram.c
//	3-gram�f�[�^�̍쐬
//	�e�L�X�g����S�p�f�[�^�̂ݒ��o����3-gram�����܂�

#include<stdio.h>
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

 /*3-gram�̏o��*/
void outputtarget(char *target) 
{
 int i=0 ;
 while((target[i]!='\0')&&(target[i+2]!='\0')&&(target[i+4]!='\0')){
  putchar(target[i++]) ;
  putchar(target[i++]) ;
  putchar(target[i]) ;
  putchar(target[i+1]) ;
  putchar(target[i+2]) ;
  putchar(target[i+3]) ;
  putchar('\n') ;
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

 /*3-gram�̏o��*/
 outputtarget(target) ;

 return 0 ;
}

