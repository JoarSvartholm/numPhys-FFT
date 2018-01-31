#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_fft_complex.h>

int main(void){


  FILE *f = fopen("gaussian.data","w");
  FILE *raw = fopen("raw.data","w");
  int noSamp = 1024;
  double T[noSamp];
  double X[noSamp];
  double dt = 1.0/noSamp;
  double sigma = 16*dt;
  gsl_complex_packed_array data = calloc(2*noSamp,sizeof(double));

  //printf("%f\n",dt );
  //genarate data
  for(int i=0;i< noSamp;i++){
    T[i] = (i-noSamp/2+1)*dt;
    X[i] = 1/(sqrt(M_PI)*sigma)*exp(-T[i]*T[i]/(sigma*sigma));
  }

  //Pack data
  for(int i=0;i<noSamp;i++){
    data[2*i] = X[i];
    data[2*i+1] = 0;
  }

  gsl_fft_complex_radix2_forward(data,1,noSamp);

  for(int i=0;i<noSamp;i++){
    fprintf(f,"%f %f ",data[2*i],data[2*i+1]);
    fprintf(raw,"%f ",X[i]);
  }
  fclose(f);
  fclose(raw);
  return 0;
}
