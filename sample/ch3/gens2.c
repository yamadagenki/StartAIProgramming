//	gens2.c
//	���������K���ɂ�镶�̐����v���O��������2
//	���������K��B�ɏ]���ĕ��𐶐����܂�
//  ���������K��B
//		�K���@	<��>��<�����偄�������偄
//�@�@�@�K���A	<������>�����`�e���偄����������
//�@�@�@�K���B	<������>������������
//�@�@�@�K���C	<������>����������
//�@�@�@�K���D	<������>�����`�e����
//�@�@�@�K���E	<������>�����`�e������
//�@�@�@�K���F	<�`�e����>�����`�e�������`�e���偄
//�@�@�@�K���G	<�`�e����>�����`�e����




#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define NMAX 8192 //�I�[�L�����ڐ��̏��
#define CHMAX 32  //�I�[�L���̒����̏��
#define NFILE "noun.txt"//�����̊i�[���ꂽ�t�@�C��
#define VFILE "verb.txt"//�����̊i�[���ꂽ�t�@�C��
#define AFILE "adj.txt"//�`�e���̊i�[���ꂽ�t�@�C��
#define DFILE "adjv.txt"//�`�e�����̊i�[���ꂽ�t�@�C��

char nlist[NMAX][CHMAX]; int nnum;
char vlist[NMAX][CHMAX]; int vnum;
char alist[NMAX][CHMAX]; int anum;
char dlist[NMAX][CHMAX]; int dnum;

void ap(void) ;
void np(void) ;
void vp(void) ;
void sentence(void) ;
int setrnd(int num) ;

/*�K���C<������>��<����> �D<������>��<�`�e��> �E<������>��<�`�e����>*/
void vp()
{
 int r ;
 r=setrnd(3) ;
 if(r==2){//�K���C
  printf("%s",vlist[setrnd(vnum)]) ;
 }
 else if(r==1){//�K���D
  printf("%s",alist[setrnd(anum)]) ;
 }
 else{//�K���E
  printf("%s",dlist[setrnd(dnum)]) ;
 }
}

/*�K���F<�`�e����>�����`�e�������`�e���偄 �G<�`�e����>�����`�e����*/
void ap()
{
 if(setrnd(2)>0){//�K���F
  ap() ;
  printf("%s",alist[setrnd(vnum)]) ;
 }
 else{//�K���G
  printf("%s",alist[setrnd(vnum)]) ;
 }
}

/*�K���A<������>�����`�e���偄���������́@�K���B�@<������>������������*/
void np()
{
 if(setrnd(2)>0){//�K���A
  ap() ;
  printf("%s��",nlist[setrnd(nnum)]) ;
 }
 else{//�K���B
  printf("%s��",nlist[setrnd(nnum)]) ;
 } 
}

/*�K���@	<��>��<�����偄�������偄*/
void sentence()
{
 np() ;//������̐���
 vp() ;//������̐���
}

/*�I�[�L�����X�g�̓ǂݍ���*/
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
 int i ;
 
 /*�����̏�����*/
 srand(65535) ;
 /*�I�[�L�����X�g�̓ǂݍ���*/
 nnum=setlist(nlist,NFILE) ;
 vnum=setlist(vlist,VFILE) ;
 anum=setlist(alist,AFILE) ;
 dnum=setlist(dlist,DFILE) ;

 for(i=0;i<50;++i){
  /*���̐���*/
  sentence() ;
  printf("�D\n") ;
}
 return 0 ;
}



