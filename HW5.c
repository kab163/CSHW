#include <stdio.h>
#include <algorithm>
#include <math.h>

int main() 
{
  /////////////////////////////INPUT/////////////////////////////////////////
  FILE *fp;
  fp = fopen("input.txt", "r");

  int N = 0;
  int B = 0;

  fscanf(fp, "%d", &B);
  fscanf(fp, "%d", &N);

  int Cost[N];
  float Prob[N];

  for (int i = 0; i < N; i++) {
    fscanf(fp, "%d %f", &Cost[i], &Prob[i]);
  }

  ////////////////////////////CALC/////////////////////////////////////////
  float REL[N+1][B+1];
  float temp = 0.0;
  float max = 0.0;

  for (int n = 1; n < N; n++) REL[n][0] = 0;
  for (int b = 0; b < B; b++) REL[0][b] = 1;

  for (int j = 1; j < N; j++) {
    for (int b = 1; b < B; b++) {
      for (int k = 1; k < (b/Cost[j]); k++) {
         temp  = REL[j-1][b-Cost[j]*k] * pow((1-(1-Prob[j])), k); 
         if (max < temp)
	   max = temp;
      }

      REL[j][b] = max;
    }
  } 

  ///////////////////////////////OUTPUT/////////////////////////////////////
 
  printf("Budget: %d\n", B);
  printf("Number of Machines: %d\n\n", N);

  printf("Iterated Version:\n");
  printf("Maximum reliability: %f\n", REL[N][B]);

  for(int n = 0; n < N; n++) {
    printf("%f copies of machine %d of cost  %d\n", REL[n][B], n+1, Cost[n]);
  }
  
  fclose(fp);
  return 0;
}
