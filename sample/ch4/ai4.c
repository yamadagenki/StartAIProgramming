//	����ׂ�l�H���\�v���O�����@ai4.c
//	���̃v���O�����́C�����ŕԓ�����l�H���\�ł�
//	�������C�ԓ����e�͌Œ�ł�
// �ԓ����L�^����wav�t�@�C���ifuun.wav,sounano.wav,soukamo.wav)��speec.exe���K�v�ł�
#include<stdio.h>
#include<stdlib.h>
#define MAXLINE 256

/*num�����̗������Z�b�g*/
int setrnd(int num)
{
 int rndno ;
 while((rndno=(double)rand()/RAND_MAX*num)==num) ;
 return rndno ;
}

/*�l�H���\�̕ԓ��쐬�i�����_���j*/
void reply(void)
{
	int rndval ;
	rndval=setrnd(4) ;
 if(rndval==0){
  system("type fuun.wav > out.wav");
  printf("������F�Ӂ`��C����ŁH\n") ;
 }
 else if(rndval==1){
  system("type sounano.wav > out.wav");
  printf("������F�����Ȃ́H\n") ;
 }
 else {
  system("type soukamo.wav >out.wav");
  printf("������F������������Ȃ���ˁE�E�E\n") ;
 }
 system("speech") ;
}

int main()
{
 char line[MAXLINE] ;//���̓o�b�t�@

 /*�I�[�v�j���O���b�Z�[�W*/
 printf("������F���b�Z�[�W���ǂ���\n");
 printf("���Ȃ��F");
 /*��b���܂��傤*/
 while(fgets(line,MAXLINE,stdin)!=NULL){
  reply() ;//�l�H���\�̕ԓ�
  printf("���Ȃ��F");
 }
 /*�G���f�B���O���b�Z�[�W*/
 printf("������F�΂��΁`��\n");
 system("type byebye.wav >out.wav");
 system("speech") ;
 return 0 ;
}
