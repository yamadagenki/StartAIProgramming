//	wav�t�@�C���ǂݎ��v���O�����@readwav.c
//	wav�t�@�C�����琔�l�����񂾃e�L�X�g�t�@�C���𐶐����܂�
//�@wav�t�@�C����8bit 8KHz�T���v�����O�@���m������p�ł�
//�@�g�����@readwav �t�@�C����

#include<stdio.h>
#include<stdlib.h>

/*data�`�����N�܂œǂݔ�΂�*/
void skipheader(FILE *fp)
{
 char ch1=' ',ch2=' ',ch3=' ',ch4 ;
 while((ch4=getc(fp))!=EOF){
  if((ch4=='a')&&(ch3=='t')&&(ch2=='a')&&(ch1=='d')) break ;
  ch1=ch2 ;ch2=ch3;ch3=ch4 ;
 }
 getc(fp) ;getc(fp);getc(fp);getc(fp);//�o�C�g���̓ǂݔ�΂�
}

 
int main(int argc,char **argv)
{
 int ch;//���̓o�b�t�@
 FILE *fp ;

 if(argc!=2){//�t�@�C�������w�肳��Ă��Ȃ�
  fprintf(stderr,"�g�����@readwav �t�@�C����\n");
  exit(1) ;
 }
 if((fp=fopen(argv[1],"rb"))==NULL){//�t�@�C�����J���Ȃ�
  fprintf(stderr,"�G���[�@�t�@�C��%s���I�[�v���ł��܂���\n",argv[1]);
  exit(1) ;
 }
 skipheader(fp) ;//data�`�����N�܂œǂݔ�΂�
 while((ch=getc(fp))!=EOF){
  printf("%u\n",ch) ;//���f�[�^�̏o��
 }

 
 return 0 ;
}
