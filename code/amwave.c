#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_fft_complex.h>

int main() {

  FILE *f = fopen("amdata.data","w");
  FILE *raw = fopen("amraw.data","w");
  double dt = 1./1024;
  double fc = 1024/128;
  int N = 1024;
  int a = 1;
  double X[N];
  double data[2*N];

  //Sampling
  for(int i = 0; i<N; i++){
    if (i%128 == 0){
      if(i%(128*2) == 0){
        a = 1;
      }
      else{
        a = 3;
      }
    }
    X[i] = a*sin(2*M_PI*fc*dt*i);
    data[2*i] = X[i];
    data[2*i+1] = 0;
  }

  gsl_fft_complex_radix2_forward(data,1,N);

  for(int i=0;i<N;i++){
    fprintf(f,"%f %f ",data[2*i],data[2*i+1]);
    fprintf(raw,"%f ",X[i]);
  }
  fclose(f);
  fclose(raw);
  return 0;
}
