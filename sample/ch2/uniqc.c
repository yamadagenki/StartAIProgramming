//	uniqc.c
//	�d���s�̐����グ�ƍ폜
//	�����s�̌J��Ԃ����폜���܂�

#include<stdio.h>
#include<string.h>
#define MAXLINE 65535 //1�s64k�o�C�g�܂ŏ����\

int main()
{
 char new[MAXLINE] ;//���͍s
 char old[MAXLINE] ;//�O�̍s
 int count=1 ;//�d���񐔂̐����グ

 /*�e�L�X�g��ǂݍ���*/
 fgets(old,MAXLINE,stdin) ;
 while(fgets(new,MAXLINE,stdin)!=NULL){
  if(strcmp(new,old)==0) ++count ;//�������s
  else{//�قȂ�s
   printf("%d\t%s",count,old);
   count=1 ;
   strcpy(old,new) ;
  }
 }
 printf("%d\t%s",count,old);

 return 0;
}

