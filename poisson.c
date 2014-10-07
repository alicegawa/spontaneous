#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include "MT.h"

#define NUM 30

double uniform(){
  return ((double)(rand()+1.0))/((double)RAND_MAX+2.0);
  //return genrand_real3();
}

int poisson_rand(double n){
  int k;
  k=0;
  n = exp(n)*uniform();
  if(n==HUGE_VAL) { 
    return k;
  }
  while(n>1){
    n *= uniform();
    k++;
  }
  return k;
}

int main(int argc, char **argv)
{
  int n,i,j;
  double ave=0.0, var=0.0;
  double tmp[NUM*NUM];
  if(argc<2){
    printf("error\n");
    return EXIT_FAILURE;
  }
  n = atoi(argv[1]);
  if(n<0){
    printf("error\n");
    return EXIT_FAILURE;
  }
  srand((unsigned)time(NULL));
  for(i=0;i<NUM;i++){
    for(j=0;j<NUM;j++){
      tmp[i*NUM+j]=poisson_rand(n);
      ave += tmp[i*NUM+j];
      printf("%5.2f ",tmp[i*NUM+j]);
    }
    printf("\n");
  }
  printf("\n");
  ave /= (NUM*NUM);
  printf("average = %7.2f (ref::%d)\n",ave,n);
  for(i=0;i<NUM;i++){
    for(j=0;j<NUM;j++){
      var += (tmp[i*NUM+j]-ave)*(tmp[i*NUM+j]-ave)/(NUM*NUM);
    }
  }
  printf("variance = %7.2f (ref::%d)\n",var,n);
  return EXIT_SUCCESS;
}
