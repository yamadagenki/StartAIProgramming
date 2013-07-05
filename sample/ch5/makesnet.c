//	makesnet.c
//	�Ӗ��l�b�g���[�N�̍쐬
//	�e�L�X�g�f�[�^����Ӗ��l�b�g���[�N�����܂�
// ��̕��т��L�q�����t�@�C�� kk.txt���K�v�ł�

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXNUM 4096 //�Ӗ��l�b�g���[�N�̍ő��
#define MAXLINE 64 //�P���̍ő咷��
#define NOPOS -1 //�T�����s�̏ꍇ�̒l
#define FILENAME  "kk.txt" //�ǂݍ��ݑΏۃt�@�C��

/*�e�L�X�g��ǂݍ���*/
int getsource(char semnet[MAXNUM][2][MAXLINE] )
{
 int numsnet=0 ;
 char line[MAXLINE] ; //�ǂݍ��ݗp�o�b�t�@
 FILE *fp;
 
 if((fp=fopen(FILENAME,"r"))==NULL){
  fprintf(stderr,"�G���[�@�t�@�C��%s������܂���\n",FILENAME);
  exit(1) ;
 }
 /*�ǂݍ��ݏ���*/
 while(fscanf(fp,"%s",line)!=EOF){
  strncpy(semnet[numsnet][0],line,MAXLINE) ;//�u�`�́v�ɂ����镔��
  if(fscanf(fp,"%s",line)!=EOF){
   strncpy(semnet[numsnet][1],line,MAXLINE) ;//�u�`�C�v�ɂ����镔��
  }
  else break ;//�Ō��1���܂����ꍇ
  ++numsnet ;
  if(numsnet>=MAXNUM){//�l�b�g���[�N��������𒴂��Ă���
	  --numsnet ;
	  printf("�x���@�Ӗ��l�b�g���[�N�̐���%d�ɐ������܂���\n",numsnet) ;
	  break ;
	 }
 }
 return numsnet ;
}
/*�Ӗ��l�b�g���[�N�̒T��*/
int searchword(char semnet[MAXNUM][2][MAXLINE],int numsnet,char line[],int flag[])
{
	int i ;
	for(i=0;i<numsnet;++i){
  if((strcmp(semnet[i][0],line)==0)&&(flag[i]==0)){//������
   flag[i]=1 ;//2��g��Ȃ��悤�ɂ���
	  break ;
	 }
 }
 if(i>=numsnet) i=NOPOS ;//������Ȃ�����
		
 return i ;
}


/* �A�z�̏���*/
void searchsnet(char semnet[MAXNUM][2][MAXLINE],int numsnet,char line[])
{
	int pos ;
	int i ;
	int flag[MAXNUM] ;//2�x�g��Ȃ����߂̃t���O

	for(i=0;i<MAXNUM;++i) flag[i]=0 ;//flag[]�̏�����
 while((pos=searchword(semnet,numsnet,line,flag))!=NOPOS){
 	printf("%s��%s�C\n",line,semnet[pos][1]) ;//�A�z�̏o��
	 strncpy(line,semnet[pos][1],MAXLINE) ;
 }
 printf("%s�́E�E�E�킩��Ȃ��I\n",line) ;//������Ȃ��̂ŏI��
}

int main()
{
 char semnet[MAXNUM][2][MAXLINE] ;//�Ӗ��l�b�g���[�N
 int numsnet ;//�Ӗ��l�b�g���[�N�̐�
 char line[MAXLINE] ;//���̓o�b�t�@

 /*�e�L�X�g��ǂݍ���*/
 numsnet=getsource(semnet) ;
 printf("%d�̈Ӗ��l�b�g���[�N��ǂݍ��݂܂���\n",numsnet) ;

 /*�Ӗ��l�b�g���[�N����������*/
 printf("�A�z���J�n����P�����͂��Ă��������D\n");
 /*�A�z���܂��傤*/
 while(scanf("%s",line)!=EOF){
  searchsnet(semnet,numsnet,line) ;
  printf("�A�z���J�n���鎟�̒P�����͂��Ă��������D\n");
 }
 printf("�������I���܂��D\n");

 return 0 ;
}

