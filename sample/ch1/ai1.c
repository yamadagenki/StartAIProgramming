//	���߂Ă̐l�H���\�v���O�����@ai1.c
//	���̃v���O�����́C��Ɍ��܂����ԓ���Ԃ��l�H���\�ł�
//	�{���ɖ��\�ł���

#include<stdio.h>
#define MAXLINE 256
int main()
{
 char line[MAXLINE] ;//���̓o�b�t�@

 /*�I�[�v�j���O���b�Z�[�W*/
 printf("������F���b�Z�[�W���ǂ���\n");
 printf("���Ȃ��F");
 /*��b���܂��傤*/
 while(fgets(line,MAXLINE,stdin)!=NULL){
  printf("������F�Ӂ`��C����ŁH\n");
  printf("���Ȃ��F");
 }
 /*�G���f�B���O���b�Z�[�W*/
 printf("������F�΂��΁`��\n");
 return 0 ;
}
