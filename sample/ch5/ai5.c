//      ai5.c
//	�v���_�N�V�������[����p�����l�H���\
//      �v���_�N�V�������[�����L�q�����t�@�C�� rule.txt���K�v�ł�

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXNO 32 //�v���_�N�V�������[���̍ő��
#define MAXSTR 64 //������̍ő咷��
#define MAXLINE 256 //1�s�̂̍ő咷��
#define NORULE -1//���[���Ƀ}�b�`���Ȃ��ꍇ�̖߂�l

#define FILENAME  "rule.txt" //�ǂݍ��ݑΏۃt�@�C��

/*�@�v���_�N�V�������[�����i�[����\����*/
struct prule{
 char str1[MAXSTR] ;// ����1
 char str2[MAXSTR] ;// ����2
 char str3[MAXSTR] ;// ����3
 char str4[MAXSTR] ;// ����4

 char action[MAXSTR] ;//�s���i����������j
} ;

/*num�ȉ��̗������Z�b�g*/
int setrnd(int num)
{
 int rndno ;
 while((rndno=(double)rand()/RAND_MAX*num)==num) ;
 return rndno ;
}

/* ���͂Ƀ}�b�`���郋�[����T��*/
int rulematch(struct prule rule[MAXNO] ,int i,char *line)
{
	if((strstr(line,rule[i].str1)!=NULL) &&
	   (strstr(line,rule[i].str2)!=NULL) &&
	   (strstr(line,rule[i].str3)!=NULL) &&
	   (strstr(line,rule[i].str4)!=NULL))
	  return 1 ;//���v����
	else 
	return  0;//���v���Ȃ�
}

/* �������̐��� */
void answer(struct prule rule[MAXNO] ,int n,char *line)
{
	int i,limit,no=0,point=0 ;

	for(i=0;i<n;++i){// �}�b�`���郋�[���̌��𒲂ׂ�
   no+=rulematch(rule,i,line) ;
 }

 if(no==0) printf("�ǂ��������Ă�������\n") ;//�}�b�`���郋�[�����Ȃ�
 else{//���Ȃ��Ƃ��P�̓}�b�`���郋�[��������
	 limit=setrnd(no) ;//���������Climit�Ԗڂ̃��[�����̗p
	 for(i=0;i<n;++i){//���[�������߂Č�������
		 if(rulematch(rule,i,line)==1){
			 if(point==limit) break ;//limit�Ԗڂ̓K�����[���𔭌�
			 ++point ;
		 }
		} 
	 printf("%s\n",rule[i].action) ;//�s���i�ԓ����̏o�́j
 }
}

/*�e�L�X�g��ǂݍ���*/
int readrule(struct prule rule[MAXNO] )
{
 int n=0 ;
 char line[MAXSTR] ; //�ǂݍ��ݗp�o�b�t�@
 FILE *fp;
 
 if((fp=fopen(FILENAME,"r"))==NULL){
  fprintf(stderr,"�G���[�@�t�@�C��%s������܂���\n",FILENAME);
  exit(1) ;
 }
 /*�ǂݍ��ݏ���*/
 while(fgets(line,MAXLINE,fp)!=NULL){
	 sscanf(line,"%s %s %s %s %s",rule[n].str1,rule[n].str2,
	                  rule[n].str3,rule[n].str4,rule[n].action) ;
	 if(strlen(rule[n].str1)>1){//���Ȃ��Ƃ��������ЂƂȏ゠��
 	 if(strcmp(rule[n].str2,"-")==0) strcpy(rule[n].str2,rule[n].str1) ;
	  if(strcmp(rule[n].str3,"-")==0) strcpy(rule[n].str3,rule[n].str2) ;
	  if(strcmp(rule[n].str4,"-")==0) strcpy(rule[n].str4,rule[n].str3) ;
  }
  ++n ;
  if(n>=MAXNO){//���[����������𒴂��Ă���
	  --n ;
	  printf("�x���@���[������%d�ɐ������܂���\n",n) ;
	  break ;
	 }
 }
 return n ;
}

int main()
{
 char line[MAXLINE] ;//���̓o�b�t�@
 struct prule rule[MAXNO] ;//�v���_�N�V�������[��
 int n ;//���[���̐�
 
 /*�����̏�����*/
 srand(65535) ;
 /*�v���_�N�V�������[���t�@�C���̓ǂݍ���*/
 n=readrule(rule) ;

 /*�I�[�v�j���O���b�Z�[�W*/
 printf("������F���āC�ǂ����܂����H\n");
 printf("���Ȃ��F");
 /*��b���܂��傤*/
 while(fgets(line,MAXLINE,stdin)!=NULL){
  printf("������F");
  answer(rule,n,line) ;//�v���_�N�V�������[���ɂ�鉞��������
  printf("���Ȃ��F");
 }
 /*�G���f�B���O���b�Z�[�W*/
 printf("������F����ł͂��b���I���܂��傤\n");
 return 0 ;
}

