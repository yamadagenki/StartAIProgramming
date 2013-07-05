//	cutnav.c
//	����Ɋ�Â������E�`�e���E�����E�`�e�����̐؂�o��
//	�e�L�X�g����S�p�f�[�^�̂ݒ��o���ďI�[�L����؂�o���܂�
//  �g����
//  �@�@cutnav �i�I�v�V�����j
//�@�I�v�V�����̗^����
//    n�܂��͂Ȃ�		�����̐؂�o��
//    v�@�@�@			�����̐؂�o��
//    a�@�@�@			�`�e���̐؂�o��
//    d      			�`�e�����̐؂�o��

#include<stdio.h>
#include<string.h>
#define MAX 65535*3 //192k�o�C�g�܂ŏ����\
#define LENGTH 64//�I�[�L�������Ɋi�[����ϐ��̃o�C�g��

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


/*�����̐؂�o��*/
void outputnoun(char *target) 
{
 int i=0 ;
 int now,last;//����(0)�E�J�^�J�i(1)�E���̑�(2)�̕�
 last=typeset(target[i],target[i+1]) ;
 while(target[i]!='\0'){
   now=typeset(target[i],target[i+1]) ;
   if((now!=last)&&(last==0)) {//�����̏I���
    putchar('\n') ;//��؂�̉��s���o��
   }
   if(now==0){//�����̏o��
    putchar(target[i]) ;
    putchar(target[i+1]) ;
   }
   last=now ;
   i+=2 ;
 }
}

/*�����E�`�e���E�`�e�����̐؂�o��*/
void outputp(char *target,char *str) 
{
 int i=0 ;
 int now,last;//����(0)�E�J�^�J�i(1)�E���̑�(2)�̕�
 char k[LENGTH] ;//�؂�o���r���̕�����
 int klength=0 ;//k�̒���
 last=typeset(target[i],target[i+1]) ;
 if(last==0) {
  strncpy(k,&(target[i]),2) ;
  klength+=2 ;
 }
 i+=2 ;
 while(target[i]!='\0'){
   now=typeset(target[i],target[i+1]) ;
   if(now==0){//������ϐ�k�ɕۑ�
	strncat(k,&(target[i]),2) ;
	klength+=2 ;
	k[klength]='\0' ;
   }
   if((now!=last)&&(last==0)){//������̏I���
    if(strncmp(&(target[i]),str,2)==0) {
        //�����̏I����str�Ŏw�肵������������
     printf("%s%s\n",k,str) ;//�I�[�L�����o��
    }
    klength=0 ;//�؂�o�������̃��Z�b�g
    k[klength]='\0' ;
   }
   last=now ;
   i+=2 ;
 }
}

int main(int argc,char **argv)
{
 char source[MAX] ;//���̓f�[�^
 char target[MAX] ;//�S�p�f�[�^
 int numchar ;//���͕�����

 /*�e�L�X�g��ǂݍ���*/
 numchar=getsource(source) ;

 /*�S�p�����̂ݎ��o��*/
 getwidechar(target,source,numchar) ;

 /*�����̐؂�o��*/
 if(argc==1)
  outputnoun(target) ;			//����
 else if(strncmp(argv[1],"n",1)==0)
  outputnoun(target) ;			//����
 else if(strncmp(argv[1],"v",1)==0)
  outputp(target,"��") ;		//����
 else if(strncmp(argv[1],"a",1)==0)
  outputp(target,"��") ;		//�`�e��
 else if(strncmp(argv[1],"d",1)==0)
  outputp(target,"��") ;		//�`�e����

 return 0 ;
}

