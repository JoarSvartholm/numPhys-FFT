
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_fft_complex.h>

int map(int i,int j,int k){
  return 2*(i*512 + j*64 + k);
}
char bin2ascii(int bit[8]){
  char let=0;
  for(int i=0;i<8;i++){
    let+= bit[i]*pow(2,(7-i));
  }
  return let;
}

int main(int argc, char const *argv[]) {

  int N = 8192;
  int Nbits = N/(8*64);
  double fc = 1024;
  double BW = 256;
  double q;
  FILE *f = fopen(argv[1],"r+");
  FILE *fftfile = fopen("noisy.data","w");
  FILE *filtdata = fopen("filtered.data","w");
  double raw[N];
  double data[2*N];
  int bit[8];

  for(int i=0;i<N;i++){
    fscanf(f,"%lf ",&raw[i]);
  }

  for(int i=0;i<N;i++){
    data[2*i]=raw[i];
    data[2*i+1] = 0;
  }

  //Make FFT
  gsl_fft_complex_radix2_forward(data,1,N);

  for(int i=0;i<2*N;i++){
    fprintf(fftfile,"%f \n",data[i]);
  }

  //Filtering
  data[0] *= exp(-0.5*fc*fc/(BW*BW));
  data[1] *= exp(-0.5*fc*fc/(BW*BW));
  for(int i=1;i<N/2;i++){
    q = (i-fc)*(i-fc)/(BW*BW);
    data[2*i] *= exp(-0.5*q);
    data[2*i+1] *= exp(-0.5*q);
    data[2*N-2*i] *= exp(-0.5*q);
    data[2*N-2*i+1] *= exp(-0.5*q);
  }

  //Inverse FFT
  gsl_fft_complex_radix2_inverse(data,1,N);

  for(int i=0;i<N;i++){
    fprintf(filtdata,"%f \n",data[2*i]);
  }

  //Decoding
  double max;
  for(int i=0;i<Nbits;i++){
    for(int j=0;j<8;j++){
      max=0;
      for(int k = 0;k<64;k++){
        if(data[map(i,j,k)]>max){
          max=data[map(i,j,k)];
        }
      }
      if(max>1){
        bit[j]=1;
      }
      else{
        bit[j]=0;
      }
    }
    printf("%c",bin2ascii(bit));
  }
  printf("\n");

  fclose(f);
  fclose(fftfile);
  fclose(filtdata);


  return 0;
}
