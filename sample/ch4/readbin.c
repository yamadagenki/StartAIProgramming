//	�o�C�i���t�@�C���ǂݎ��v���O�����@readbin.c
// �o�C�i���t�@�C����ǂݍ���ŉ�ʂɒl���o�͂��܂�
//�@�g�����@readbin �t�@�C����

#include<stdio.h>
#include<stdlib.h>

int main(int argc,char **argv)
{
 int ch;//���̓o�b�t�@
 FILE *fp ;

 if(argc!=2){//�t�@�C�������w�肳��Ă��Ȃ�
  fprintf(stderr,"�g�����@readbin �t�@�C����\n");
  exit(1) ;
 }
 if((fp=fopen(argv[1],"rb"))==NULL){//�t�@�C�����J���Ȃ�
  fprintf(stderr,"�G���[�@�t�@�C��%s���I�[�v���ł��܂���\n",argv[1]);
  exit(1) ;
 }
 while((ch=getc(fp))!=EOF){
	 if((ch>=32)&&(ch<=127))//�p���L���͈̔�
   printf("%u\t%c\n",ch,ch) ;//�o�C�i���f�[�^�̒l�ƁC�����Ƃ��Ă̏o��
  else
   printf("%u\n",ch) ;//�o�C�i���f�[�^�̒l�̏o��
 }

 
 return 0 ;
}
