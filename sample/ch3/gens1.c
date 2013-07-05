//	gens1.c
//	���������K���ɂ�镶�̐����v���O�������̂P
//	���������K��A�ɏ]���ĕ��𐶐����܂�
//  ���������K���@A
//    �K���@	<��>��<�����偄�������偄
//  �@�K���A	<������>������������
//�@�@�K���B�@ <������>����������


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define NMAX 8192 //�I�[�L�����ڐ��̏��
#define CHMAX 32  //�I�[�L���̒����̏��
#define NFILE "noun.txt"//�����̊i�[���ꂽ�t�@�C��
#define VFILE "verb.txt"//�����̊i�[���ꂽ�t�@�C��

void np(char nlist[NMAX][CHMAX],int nnum) ;
void vp(char vlist[NMAX][CHMAX],int vnum) ;
void sentence(char nlist[NMAX][CHMAX],int nnum,char vlist[NMAX][CHMAX],int vnum) ;
int setrnd(int num) ;

/*�K���B�@<������>����������*/
void vp(char vlist[NMAX][CHMAX],int vnum)
{
 printf("%s",vlist[setrnd(vnum)]) ;
 
}

/*�K���A		<������>������������*/
void np(char nlist[NMAX][CHMAX],int nnum)
{
 printf("%s��",nlist[setrnd(nnum)]) ;
 
}

/*�K���@	<��>��<�����偄�������偄*/
void sentence(char nlist[NMAX][CHMAX],int nnum,char vlist[NMAX][CHMAX],int vnum)
{
 np(nlist,nnum) ;//������̐���
 vp(vlist,vnum) ;//������̐���
}

/*�������X�g�E�������X�g�̓ǂݍ���*/
int setlist(char list[NMAX][CHMAX],char *filename)
{
 FILE *fp;
 char line[CHMAX] ;
 int i=0 ;

 if((fp=fopen(filename,"r"))==NULL){
  fprintf(stderr,"�G���[�@�t�@�C��%s������܂���\n",filename);
  exit(1) ;
 }

 while(fgets(line,CHMAX,fp)!=NULL){
  strncpy(list[i],line,CHMAX) ;
  list[i][strlen(line)-1]='\0' ;
  ++i ;
 }
 fclose(fp) ;
 return i ;//���͌���Ԃ�
}

/*num�����̗������Z�b�g*/
int setrnd(int num)
{
 int rndno ;
 while((rndno=(double)rand()/RAND_MAX*num)==num) ;
 return rndno ;

}

int main()
{
 char nlist[NMAX][CHMAX] ;//�������X�g
 char vlist[NMAX][CHMAX] ;//�������X�g
 int nnum,vnum ;//���X�g�̍��ڐ�
 int i ;
 
 /*�����̏�����*/
 srand(65535) ;
 /*�������X�g�Ɠ������X�g�̓ǂݍ���*/
 nnum=setlist(nlist,NFILE) ;
 vnum=setlist(vlist,VFILE) ;

 for(i=0;i<50;++i){
  /*���̐���*/
  sentence(nlist,nnum,vlist,vnum) ;
  printf("�D\n") ;
}
 return 0 ;
}



