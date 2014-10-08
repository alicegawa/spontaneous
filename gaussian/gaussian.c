#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "MT.h"
#define NUM 1000000
#define R 3000
int main()
{
  int i;
  int counter = 0;
  double r,r2,rec[NUM];
  double sum=0.0, v=0.0;
  double max = -1000;
  static int sw = 0;
  static double tmp_r;
  srand((unsigned)time(NULL));
  for(i=0;i<NUM;i++){
    r = ((double)rand()+1.0)/((double)RAND_MAX + 2.0);
    r2 = ((double)rand()+1.0)/((double)RAND_MAX + 2.0);
    //r = genrand_real3();
    //r2 = genrand_real3();
    rec[i] =  sqrt(2.0)*sqrt(-2.0*log(r))*sin(2.0*M_PI*r2);
    rec[i] /= 3000.0;
    if(rec[i]<0){
      counter++;
    }
    if(max<fabs(rec[i])){
      max = fabs(rec[i]);
    }
    //rec[i] *= 0.13;
      
    sum += rec[i];
  }
  sum /= (double)NUM;
  for(i=0;i<NUM;i++){
    v += (rec[i]-sum)*(rec[i]-sum);
  }
  v /= (double)NUM;
  printf("counter = %d\n",counter);
  printf("M_PI =  %lf \n",M_PI);
  printf("平均 = %lf \n", sum);
  printf("分散 = %lf \n", v);
  printf("参考値 = %lf \n",1.0/sqrt(0.25));
  printf("最大値 = %lf \n",max);
  return 0;
}
