//	��`�I�A���S���Y���ɂ��T���v���O����  ga_b.c
// ga_a�ƕ]�����@���قȂ�܂�(fitness�֐����قȂ�܂��j


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define POOLSIZE 30  //�v�[���T�C�Y
#define RULESIZE 4  //��`�q�̎����[���̐�
#define LOCUSSIZE 4 //�ЂƂ̃��[��������`�q���̐�

#define GMAX 3000 //�ł��؂萢��
#define MRATE 0.1 //�ˑR�ψٗ�

#define LOWERLIMIT 1000 //��`�q���󎚂���Œ�K���x
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
 int j,fvalue=0,fpenalty=0,sscore,totalfitness ;
 for(j=0;j<RULESIZE;++j){ 
  sscore=score(sgene[j],lines,lineno) ;
  fpenalty+=sscore*sscore ;
  fvalue+=sscore ;
 }
 if(fvalue>=lineno) fvalue=lineno ;//����𑍃��[�����ɐ���
 totalfitness=fvalue*fvalue-fpenalty ;
 if(totalfitness<0) totalfitness=0 ;
 return totalfitness ;
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
void mutation(char midgene[POOLSIZE*2][RULESIZE][LOCUSSIZE])
{
 int i,j,k ;

 for(i=0;i<POOLSIZE*2;++i)
   for(j=0;j<RULESIZE;++j)
    for(k=0;k<LOCUSSIZE;++k){
     if(setrnd(1.0/MRATE)<1){
      midgene[i][j][k]='A'+setrnd(26) ;//�ˑR�ψ�
     }
    }
}


/*midgene�v�[���̓K���x�̌v�Z*/
void setfvalue(char midgene[POOLSIZE*2][RULESIZE][LOCUSSIZE],
            int fvalue[],char lines[MAXLINES][LINESIZE],int lineno)
{
 int i ;
 for(i=0;i<POOLSIZE*2;++i)
  fvalue[i]=fitness(midgene[i],lines,lineno)+1 ;
}

/*�K���x�̍��v�̌v�Z*/
int sumupfvalue(int fvalue[])
{
 int i;
 int sum=0 ;
 for(i=0;i<POOLSIZE*2;++i)
  sum+=fvalue[i] ;
 return sum ;
}

/*�|�C���^�̃C���N�������g*/
int incpoint(int point)
{
 ++point ;
 if(point>=POOLSIZE*2) point=0 ;//�͂��߂ɖ߂�
 return point ;
}
	
/*���[���b�g���񂵂ĂЂƂ�`�q��I��*/
int roulette(int fvalue[POOLSIZE*2],int sumf,int point)
{
 int step ;//���[���b�g�̒l
 int acc=0 ;//�K���x�̐ώZ�l

 step=setrnd(sumf);//���[���b�g�̒l������
 while(acc<step){
  point=incpoint(point) ;
  acc+=fvalue[point] ;
 }
 fvalue[point]=0 ;//�Q�x�I�΂�Ȃ��悤�ɂ���
 return point ;
}

/*�I��*/
void selection(char gene[POOLSIZE][RULESIZE][LOCUSSIZE],char midgene[POOLSIZE*2][RULESIZE][LOCUSSIZE],
   char lines[MAXLINES][LINESIZE],int lineno)
{
 int i,j,k ;
 int fvalue[POOLSIZE*2] ;//midgene�v�[���̓K���x
 int sumf ;//�K���x�̍��v�l
 int point=0 ;//���[���b�g�̃X�^�[�g�ꏊ
 int midpoint ;
 
 setfvalue(midgene,fvalue,lines,lineno) ;//fvalue�ɒl���Z�b�g
 sumf=sumupfvalue(fvalue) ;//�K���x�̍��v�l���v�Z
 for(i=0;i<POOLSIZE;++i){//���[���b�g�ɂ��������đI��
  midpoint=roulette(fvalue,sumf,point) ;
  for(j=0;j<RULESIZE;++j)
   for(k=0;k<LOCUSSIZE;++k)
    gene[i][j][k]=midgene[midpoint][j][k]; 
 }
}

/*�|�C���^�̃C���N�������g(groulette�p�j*/
int gincpoint(int point)
{
 ++point ;
 if(point>=POOLSIZE) point=0 ;//�͂��߂ɖ߂�
 return point ;
}
	
/*���[���b�g���񂵂ĂЂƂ�`�q��I��(�����p�j*/
int groulette(int fvalue[POOLSIZE],int sumf,int point)
{
 int step ;//���[���b�g�̒l
 int acc=0 ;//�K���x�̐ώZ�l

 step=setrnd(sumf);//���[���b�g�̒l������
 while(acc<step){
  point=gincpoint(point) ;
  acc+=fvalue[point] ;
 }
// fvalue[point]=0 ;//�Q�x�I�΂�Ă��ǂ�
 return point ;
}

/*��l����*/
void singlecrossover(char p1[RULESIZE][LOCUSSIZE],char p2[RULESIZE][LOCUSSIZE],
                char c1[RULESIZE][LOCUSSIZE],char c2[RULESIZE][LOCUSSIZE])
{
	int j,k ;

 for(j=0;j<RULESIZE;++j){
  for(k=0;k<LOCUSSIZE;++k){
   if(setrnd(2)>0){
    c1[j][k]=p1[j][k]; 
    c2[j][k]=p2[j][k];
   }
   else{
    c1[j][k]=p2[j][k]; 
    c2[j][k]=p1[j][k];
   }
  }
 }
}

/*����*/
void crossover(char midgene[POOLSIZE*2][RULESIZE][LOCUSSIZE],char gene[POOLSIZE][RULESIZE][LOCUSSIZE]
                ,char lines[MAXLINES][LINESIZE],int lineno)
{
 int i,j,k ;
 int gfvalue[POOLSIZE] ;//gene�v�[���̓K���x
 int gsumf=0 ;//�K���x�̍��v�l
 int point=0 ;//���[���b�g�̃X�^�[�g�ꏊ
 int midpoint ;
 
 for(i=0;i<POOLSIZE;++i)
  gfvalue[i]=fitness(gene[i],lines,lineno)+1 ;//fvalue�ɒl���Z�b�g
 for(i=0;i<POOLSIZE;++i)
  gsumf+=gfvalue[i] ;//�K���x�̍��v�l���v�Z
 for(i=0;i<POOLSIZE;++i){//���[���b�g�ɂ��������đI��
  singlecrossover(gene[point=groulette(gfvalue,gsumf,point)],
                  gene[point=groulette(gfvalue,gsumf,point)],
                  midgene[2*i],midgene[2*i+1]) ;
 }

}


int main()
{
 char gene[POOLSIZE][RULESIZE][LOCUSSIZE] ;//��`�q�v�[��
 char midgene[POOLSIZE*2][RULESIZE][LOCUSSIZE] ;//���B���̈�`�q�v�[��
 char lines[MAXLINES][LINESIZE] ;//�L�[���[�h�̃f�[�^
 int lineno ;//�L�[���[�h�f�[�^�̍s��
 int generation ;
 srand(0) ;//�����̏�����
 lineno=readlines(lines) ;//�L�[���[�h�f�[�^�̓ǂݍ���
 initgene(gene) ;//��`�q�v�[���̏�����
 for(generation=0;generation<GMAX;++generation){
  printf("��%d���� ���ϓK���x %f\n",generation,fave(gene,lines,lineno)) ;
  printgene(gene,lines,lineno) ;//��`�q�v�[���̏o��
  crossover(midgene,gene,lines,lineno) ;//����
  mutation(midgene) ;//�ˑR�ψ�
  selection(gene,midgene,lines,lineno) ;//�I��
 }
  printf("��%d���� ���ϓK���x %f\n",generation,fave(gene,lines,lineno)) ;
  printgene(gene,lines,lineno) ;//��`�q�v�[���̏o��

 return 0 ;
}
