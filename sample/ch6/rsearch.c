//	�����_���T�[�`�v���O����  rsearch.c
//	�����_���T�[�`�ɂ�����T�����܂�


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define POOLSIZE 30  //�v�[���T�C�Y
#define RULESIZE 4  //��`�q�̎����[���̐�
#define LOCUSSIZE 4 //�ЂƂ̃��[��������`�q���̐�

#define GMAX 10000 //�ł��؂萢��
#define MRATE 0.1 //�ˑR�ψٗ�

#define LOWERLIMIT 0 //��`�q���󎚂���Œ�K���x
#define MAXLINES 64 //�L�[���[�h�̑g�ݍ��킹�̍ő吔
#define LINESIZE 64 //�L�[���[�h�f�[�^�̍s�T�C�Y

/*num�ȉ��̗������Z�b�g*/
int setrnd(int num)
{
 int rndno ;
 while((rndno=(double)rand()/RAND_MAX*num)==num) ;
 return rndno ;

}

/*��`�q�v�[���̏�����*/
void initgene(char gene[POOLSIZE][RULESIZE][LOCUSSIZE])
{
 int i,j,k ;
 for(i=0;i<POOLSIZE;++i)
  for(j=0;j<RULESIZE;++j)
   for(k=0;k<LOCUSSIZE;++k)
    gene[i][j][k]='A'+setrnd(26) ;//�����_���ɏ����l���Z�b�g
}

/*���[��������f�[�^�ƃ}�b�`���邩���v�Z*/
int score(char *singlerule,char lines[MAXLINES][LINESIZE],int lineno)
{
 int i,l ;
 int score=0 ;//�}�b�`�����f�[�^�̍s��
 int localscore ;
 for(l=0;l<lineno;++l){
  localscore=0 ;
  for(i=0;i<LOCUSSIZE;++i)//�e�L�[���[�h�𒲂ׂ�
   if(strchr(lines[l],singlerule[i])!=NULL) ++localscore ;
  if(localscore>=LOCUSSIZE) ++score ;//���S�Ɉ�v
 }
 return score ;
}

/*i�Ԗڂ̐��F�̂̓K���x���v�Z*/
int fitness(char sgene[RULESIZE][LOCUSSIZE],char lines[MAXLINES][LINESIZE],int lineno)
{
 int j,fvalue=0 ;
 for(j=0;j<RULESIZE;++j) 
  fvalue+=score(sgene[j],lines,lineno) ;
 return fvalue ;
}

/*��`�q�v�[���̏o��*/
void printgene(char gene[POOLSIZE][RULESIZE][LOCUSSIZE],char lines[MAXLINES][LINESIZE],int lineno)
{
 int i,j,k ;
 int fvalue ;
 for(i=0;i<POOLSIZE;++i){
  fvalue=fitness(gene[i],lines,lineno) ;
  if(fvalue>=LOWERLIMIT){//���̏�����ύX����ƕ\���ʂ𒲐��ł��܂�
   printf("%3d : ",i) ;
   for(j=0;j<RULESIZE;++j){
    for(k=0;k<LOCUSSIZE;++k)
     printf("%c ",gene[i][j][k]) ;
    if(j<RULESIZE-1) printf(", ") ;
   }
   printf("     %d\n",fvalue) ;//�K���x�̏o��
  }
 }
}

/*��`�q�v�[���̐��㕽�ϓK���x�̌v�Z*/
double fave(char gene[POOLSIZE][RULESIZE][LOCUSSIZE],char lines[MAXLINES][LINESIZE],int lineno)
{
 int i ;
 double fsum=0.0 ;
 for(i=0;i<POOLSIZE;++i){
  fsum+=fitness(gene[i],lines,lineno) ;
 }
 return fsum/POOLSIZE ;
}

/*�L�[���[�h�f�[�^�̓ǂݍ���*/
int readlines(char lines[MAXLINES][LINESIZE])
{
 int n=0 ;

 /*�ǂݍ��ݏ���*/
 while(fgets(lines[n++],LINESIZE,stdin)!=NULL){
  if(n>=MAXLINES){//�s��������𒴂��Ă���
   --n ;
   printf("�x���@�s����%d�ɐ������܂���\n",n) ;
   break ;
  }
  if(strlen(lines[n-1])<=2){//�L�[���[�h�̋L�q����Ă��Ȃ��s�̏���
   --n;
   break ;
  }
 }
 return n ;
}
/*�ˑR�ψ�*/
void mutation(char gene[POOLSIZE][RULESIZE][LOCUSSIZE])
{
 int i,j,k ;

 for(i=0;i<POOLSIZE;++i)
  for(j=0;j<RULESIZE;++j)
   for(k=0;k<LOCUSSIZE;++k){
    if(setrnd(1.0/MRATE)<1){
     gene[i][j][k]='A'+setrnd(26) ;//�ˑR�ψ�
    }
   }
}

int main()
{
 char gene[POOLSIZE][RULESIZE][LOCUSSIZE] ;//��`�q�v�[��
 char lines[MAXLINES][LINESIZE] ;//�L�[���[�h�̃f�[�^
 int lineno ;//�L�[���[�h�f�[�^�̍s��
 int generation ;
 srand(65535) ;//�����̏�����
 lineno=readlines(lines) ;//�L�[���[�h�f�[�^�̓ǂݍ���
 initgene(gene) ;//��`�q�v�[���̏�����
 for(generation=0;generation<GMAX;++generation){
  printf("��%d���� ���ϓK���x %f\n",generation,fave(gene,lines,lineno)) ;
  printgene(gene,lines,lineno) ;//��`�q�v�[���̏o��
  mutation(gene) ;//�ˑR�ψ�
 }
 return 0 ;
}
