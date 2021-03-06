#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#define REPEAT 100
#define DATASIZE 1000

double MyBigDataArrayIn[DATASIZE][DATASIZE];
double MyBigDataArrayOut[DATASIZE][DATASIZE];

//return the wallclock time in seconds
double wallclock(){
  struct timeval tv;
  double t;

  gettimeofday(&tv, NULL);

  t = (double)tv.tv_sec;
  t += ((double)tv.tv_usec)/1000000.0;
  return t;
}

int main(int argc, char *argv[]){
  int i,j;
  double coef[5] = {1.0,2.0,3.0,4.0,5.0};
  unsigned int checksum = 0;
  double tstart, tend;
  int k;
  // init the data
  for (i=0;i< DATASIZE; i++){
    for (j=0;j< DATASIZE; j++){
      MyBigDataArrayIn[i][j] = i*j;
      MyBigDataArrayOut[i][j] = 0;
    }
  }
  // compute some stuff - does not matter here
  tstart = wallclock();
  for (k=0;k<REPEAT;k++){
    for (i=1;i< DATASIZE-1; i++){
      for (j=1;j< DATASIZE-1; j++){
	MyBigDataArrayOut[i][j] = MyBigDataArrayOut[i][j] +  coef[0] * MyBigDataArrayIn[i][j] 
	                        + coef[1] * MyBigDataArrayIn[i-1][j] 
	                        + coef[2] * MyBigDataArrayIn[i+1][j]
	                        + coef[3] * MyBigDataArrayIn[i][j-1]
	                        + coef[4] * MyBigDataArrayIn[i][j+1];

      }
    }
  }
  tend = wallclock();
  printf("Executing time is %f sec.\n",tend-tstart);
  // compute a check sum on result
  for (i=0;i< DATASIZE; i++){
    for (j=0;j< DATASIZE; j++){
      checksum = checksum + (unsigned int) MyBigDataArrayOut[i][j];
    }
  }
  // display the check sum same value in serial or parallel execution
  printf("checksum is %u\n",checksum);
  return 0;
}
