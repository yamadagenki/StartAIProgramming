//	genwf.c
//	�V�C�\����h����ׂ�h�v���O����
//	���������K���b�ɏ]���ēV�C�\��𐶐����܂�
//  ���������K���b
//	�K���@	<��>��<�n�恄�����ԑс����V�C��
// �K���A	<�n��>�������n��
// �K���B	<�n��>�����䌧
// �K���C	<���ԑ�>��������
// �K���D	<���ԑ�>��������
// �K���E	<�V�C>�����V�C���Ƃ���ɂ�聃�V�C��
// �K���F	<�V�C>������
// �K���G	<�V�C>���܂�
// �K���H	<�V�C>���J
// ���s�ɂ́C�e�L�X�g�`���ŉ����f�[�^���i�[�����ȉ���8�̃t�@�C�����K�v�ł��D
// toukyouchihou.txt fukuiken.txt
// kyouha.txt asuha.txt
// hare.txt kumori.txt ame.txt
// tokoroniyori.txt



#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void weather(void) ;
void timezone(void) ;
void region(void) ;
void sentence(void) ;
int setrnd(int num) ;

/*�K���E	<�V�C>�����V�C���Ƃ���ɂ�聃�V�C��*/
/*�K���F	<�V�C>������ �K���G	<�V�C>���܂�  �K���H	<�V�C>���J*/
void weather()
{
	int rndval ;
	rndval=setrnd(4) ;
 if(rndval==0){//�K���E
  weather() ;
  system("type tokoroniyori.txt >> out.txt");
  printf("�Ƃ���ɂ��") ;
  weather() ;
 }
 else if(rndval==1){//�K���F
  system("type hare.txt >> out.txt");
  printf("����") ;
 }
 else if(rndval==2){//�K���G
  system("type kumori.txt >> out.txt");
  printf("�܂�") ;
 }
 else {//�K���H
  system("type ame.txt >> out.txt");
  printf("�J") ;
 } 
}


/*�K���C	<���ԑ�>��������   �K���D	<���ԑ�>��������*/
void timezone()
{
 if(setrnd(2)>0){//�K���C
  system("type kyouha.txt >> out.txt");
  printf("������") ;
 }
 else{//�K��1�D
  system("type asuha.txt >> out.txt");
  printf("������") ;
 } 
}

/*�K���A<�n��>�������n���@�K���B�@<�n��>�����䌧*/
void region()
{
 if(setrnd(2)>0){//�K���A
  system("type toukyouchihou.txt > out.txt");
  printf("�����n��") ;
 }
 else{//�K���B
  system("type fukuiken.txt > out.txt");
  printf("���䌧") ;
 } 
}

/*�K���@	<��>��<�n�恄�����ԑс����V�C��*/
void sentence()
{
 region() ;//�n��̐���
 timezone() ;//���ԑт̐���
 weather();//�V�C�̐���
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
 char ans ;
 
 /*�����̏�����*/
 srand(65535) ;

 /*���̐���*/
 while(1){
  sentence() ;
  printf("\n") ;
  printf("����ŗǂ��ł����H(y/n)\n") ;
  scanf("%c",&ans) ;
  if(ans=='y') break ;
}

 return 0 ;
}



