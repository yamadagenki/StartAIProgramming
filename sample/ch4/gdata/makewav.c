//	wav�t�@�C�������v���O�����@makewav.c
//	���l�����񂾃e�L�X�g�t�@�C������wav�t�@�C���𐶐����܂�
// ��������wav�t�@�C����8bit 8KHz�T���v�����O�@���m�����ł�
//  �w�b�_ ��44�o�C�g�C�f�[�^�`�����N�͉ϒ��ł�
//  �g����  makewav �o�̓t�@�C���� < �����f�[�^�e�L�X�g�t�@�C��

#include<stdio.h>
#include<stdlib.h>
#define MAX 8000*40 //40�b���̃f�[�^���܂őΉ�

/*�e�L�X�g�t�@�C���̓ǂݍ���*/
unsigned int readdata(char sounddata[])
{
 unsigned int n=0 ;//���̓f�[�^�̌�

 while(scanf("%d",&sounddata[n++])!=EOF)
	 if(n>=MAX){
		 fprintf(stderr,"�x���F���̓f�[�^�����ő�l�ɒB���܂���\n") ;
		 break ;
	}
 return n-1 ;
}

/*4�o�C�g�̃f�[�^���o�C�i���ŏo��*/
void putword(int w,FILE *fp)
{
 fwrite(&w,sizeof(int),1,fp) ;
} 

/*wav�t�@�C���w�b�_�̍쐬*/
void makeheader(unsigned int slength,FILE *fp)
{
 fprintf(fp,"RIFF") ;//RIFF
 putword(slength+36,fp) ;//�t�@�C���T�C�Y-8(=36+�f�[�^��)
 fprintf(fp,"WAVE") ;//WAVE�t�@�C��
 fprintf(fp,"fmt ") ;//fmt�`�����N�̊J�n
 putword(16,fp) ;//fmt�`�����N��(16byte)
 putc(1,fp);putc(0,fp);//�t�H�[�}�b�g�h�c
 putc(1,fp);putc(0,fp);//�`�����l�����i���m�����j
 putword(8000,fp) ;//�T���v�����O���[�g�i8000Hz)
 putword(8000,fp) ;//�f�[�^���x�i8000Hz)
 putc(1,fp);putc(0,fp);//�u���b�N�T�C�Y
 putc(8,fp);putc(0,fp);//bits/sample
 fprintf(fp,"data") ;//data�`�����N
 putword(slength,fp) ;//�g�`�f�[�^�̃o�C�g��
}


int main(int argc,char **argv)
{
 char sounddata[MAX] ;//���f�[�^
 unsigned int slength ;
 FILE *fp ;

 if(argc!=2){//�t�@�C�������w�肳��Ă��Ȃ�
  fprintf(stderr,"�g�����@makewav �o�̓t�@�C����\n");
  exit(1) ;
 }
 if((fp=fopen(argv[1],"wb"))==NULL){//�t�@�C�����J���Ȃ�
  fprintf(stderr,"�G���[�@�t�@�C��%s���I�[�v���ł��܂���\n",argv[1]);
  exit(1) ;
 }
 
 /*���l�i�e�L�X�g�j�̓ǂݍ���*/
 slength=readdata(sounddata) ;
 
 /*�w�b�_���̏o��*/
 makeheader(slength,fp) ;
 /*�f�[�^�̏o��*/
 fwrite(sounddata,sizeof(char),slength,fp) ;
 return 0 ;
}
