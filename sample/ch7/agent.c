// �����w�K�ɂ�邶��񂯂�G�[�W�F���g�v���O����(�����jagent.c
// ���̃v���O�����́C����񂯂�G�[�W�F���g�Ɗ��̗����̋@�\���ʂ����܂�
// ���s����ɂ́C�����G�[�W�F���g�ɗ^�����̌n����i�[�����t�@�C��hands.txt���K�v�ł�
// agent�v���O�����������ꂽ�f�B���N�g���ɂ́C������Ԃ̓r���o�߂�ۑ�����t�@�C��int.txt���쐬����܂�

#include<stdio.h>
#include<stdlib.h>
#define MAXLINE 256
#define GU 0    //�O�[
#define CYOKI 1 //�`���L
#define PA 2   //�p�[
#define INITVAL 10 //�헪�\�̏����l
#define FILENAME "int.txt" //������Ԃ̓r���o�߂�ۑ�����t�@�C��
#define HANDSFILENAME "hands.txt" //�����G�[�W�F���g�ɗ^�����̌n����i�[�����t�@�C��

/*num�ȉ��̗������Z�b�g*/
int setrnd(int num)
{
 int rndno ;
 while((rndno=(double)rand()/RAND_MAX*num)==num) ;
 return rndno ;

}

/*�w�K*/
void learning(int reward,int last_my,int last_opp,int q[3][3],FILE *fp)
{
 int i,j,alpha ;
 for(i=0;i<3;++i){
  if(i==last_my) alpha=1 ;
  else alpha=-1 ;
  /*��V�Ɋ�Â���q���X�V*/
  if((q[last_opp][i]+alpha*reward)>0) q[last_opp][i]+=alpha*reward ;
  }
  /*�t�@�C���ւ̓�����Ԃ̏����o��*/
  for(i=0;i<3;++i)
   for(j=0;j<3;++j)
    fprintf(fp,"%d ",q[i][j]) ;
  fprintf(fp,"\n") ;
}
/*���[���b�g���񂵂Ď��I��*/
int roulette(int pq[3])
{
 int step ;//���[���b�g�̒l
 int acc=0 ;//�K���x�̐ώZ�l
 int point=0;

 step=setrnd(pq[0]+pq[1]+pq[2]);//���[���b�g�̒l������
 while(acc<=step){
  acc+=pq[point] ;
  ++point ;
 }
 return point-1 ;
}

/* �s���I���i��̌���j*/
int selectaction(int opphand,int q[3][3])
{
 return roulette(q[opphand]) ;
}

/*��V�̐ݒ�*/
int setreward(int opphand,int last_my)
{
 int rtable[3][3]={{0,-1,1},{1,0,-1},{-1,1,0}} ;
 return rtable[opphand][last_my] ;
}

int main()
{
 char line[MAXLINE] ;//���̓o�b�t�@
 int opphand,last_opp ;//����̎�
 int myhand,last_my ;//�����̎�
 int reward ;//��V
 int q[3][3]={{INITVAL,INITVAL,INITVAL},
                   {INITVAL,INITVAL,INITVAL},
                   {INITVAL,INITVAL,INITVAL}} ;//�헪�\
 FILE *fp;//�r���o�߂��i�[����t�@�C���̃t�@�C���|�C���^
 FILE *handsfp;//���̎�̌n��t�@�C���̃t�@�C���|�C���^

 if((fp=fopen(FILENAME,"w"))==NULL){
  fprintf(stderr,"�G���[�@�t�@�C��%s���J���܂���\n");
  exit(1) ;
 }
 
 if((handsfp=fopen(HANDSFILENAME,"r"))==NULL){
  fprintf(stderr,"�G���[�@�t�@�C�����J���܂���\n");
  exit(1) ;
 }
 
 srand(32767);//�����̏�����
 last_my=last_opp=GU ;//�ŏ��̓O�[
 /*����񂯂�̌J��Ԃ�*/
 while(fgets(line,MAXLINE,handsfp)!=NULL){//�ŏ��ɑO��̎��ǂ�
  sscanf(line,"%d",&opphand) ;
  reward=setreward(opphand,last_my) ;//��V�̐ݒ�
  if(reward!=0) learning(reward,last_my,last_opp,q,fp) ;//��V�Ɋ�Â��w�K
  printf("%d %d ",opphand,reward) ;//�O��̌��ʂ̏o��
  printf("%d\n",(last_my=selectaction(opphand,q))) ;//���̍s�������肷��
  last_opp=opphand ;//�O��̎���o���Ă���
 }

 return 0 ;
}
