#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "MT.h"

#define NUM 1000
#define THETA 0.5//1.0//1.05//3.0
#define KAPPA 1000//.01//0.025//4
double uniform(){
  return genrand_real3();
  // return ((double)(rand()+1.0))/((double)RAND_MAX+2.0);
}

double rand_gamma(double theta, double kappa){
  int int_kappa;
  double frac_kappa;
  
  int_kappa = (int)kappa;
  frac_kappa = kappa - (double)int_kappa;

  double u,uu;
  double b,p,x_frac,x_int;
  int i;
 
  
  x_int = 0;
  for(i=0;i<int_kappa;i++){
    x_int += -log(uniform());
  }

  if(fabs(frac_kappa)<0.01) x_frac=0;
  else{
    b = (exp(1.0)+frac_kappa)/exp(1.0);
    while(1){
      u = uniform();
      p = b*u;
      uu = uniform();
      if(p<=1.0){
	x_frac = pow(p,1.0/frac_kappa);
	if(uu<=exp(-x_frac)) break;
      }
      else{
	x_frac = -log((b-p)/frac_kappa);
	if(uu<=pow(x_frac,frac_kappa-1.0)) break;
      }
    }
  }
  //return x_int*theta;
  return (x_int+x_frac)*theta;
}

int main(){
  int i;
  double ave = 0.0, var = 0.0;
  double gam[NUM];
  double max=-100, min = 100;
  FILE *fp;
  if((fp=fopen("result.dat","w"))==NULL){
    printf("file open error\n");
    exit(1);
  }

  
  srand((unsigned)time(NULL));
  for(i=1;i<=NUM;i++){
    printf("%lf ",gam[i-1]=rand_gamma(THETA,KAPPA));
    fprintf(fp,"%lf \n",gam[i-1]);
    ave += gam[i-1]/(double)NUM;
    if(gam[i-1]>max){
      max = gam[i-1];
    }
    if(gam[i-1]<min){
      min = gam[i-1];
    }
    if(i%((int)sqrt((double)NUM))==0){
      printf("\n");
    }
  }

  for(i=0;i<NUM;i++){
    var += (gam[i]-ave)*(gam[i]-ave)/(double)NUM;
  }
  printf("\naverage = %lf (ref:%lf)\n",ave,KAPPA*THETA);
  printf("variance = %lf (ref::%lf)\n",var, KAPPA*THETA*THETA);
  printf("max = %lf\t min = %lf\n",max,min);
  fclose(fp);
  return 0;
}
