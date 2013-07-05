//	sortn.c
//	�s���̐��l�ɂ��s�𐮗񂵂܂�
//�@�s���ɐ���������C�^�u�ŋ�؂��Ďc��̕����񂪂���f�[�^���������܂�
//  n-gram����p�ł�����C1�s��16byte�ȓ��ɐ������Ă��܂�

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LINESIZE 16 //1�s16�o�C�g�܂ŏ����\
#define MAX 65536*3 //192k�s�܂ŏ����\  

char lines[MAX][LINESIZE] ; //����Ώ�

/*��r�֐�*/
int cmpdata(const char *a,const char *b)
{
 int ia,ib ;
 ia=atoi(a) ;
 ib=atoi(b) ;
 if(ia>ib) return -1;
 else if(ia<ib) return 1 ;
 else return 0 ;
}

int main()
{
 char buf[LINESIZE] ;//�ǂݍ��݃o�b�t�@
 int pos=0 ;//�ǂݍ��ݍs���̃J�E���^
 int i ;
 
 /*�e�L�X�g��ǂݍ���*/
 while(fgets(buf,LINESIZE,stdin)!=NULL){
   strcpy(lines[pos],buf) ;
   if((++pos)>=MAX){ fprintf(stderr,"File too big.\n") ;exit(1);}
  }
 /*����*/
 qsort(lines,pos,LINESIZE,(int (*)(const void *,const void *))cmpdata) ;
 /*�o��*/
 for(i=0;i<pos;++i)
  printf("%s",lines[i]) ;
  
 return 0;
}
