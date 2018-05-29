//#include "stdafx.h"
#include <math.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{ 	
	FILE *fp;
	fp = fopen("input.txt", "r");

	int N = 0;
	int B = 0;

	fscanf(fp, "%d", &B);
	fscanf(fp, "%d", &N);

	int Cost[N];
	float rProb[N];
	int out[N];

	for (int i = 0; i < N; i++) {
  	  fscanf(fp, "%d %f", &Cost[i], &rProb[i]);
	}

	float REL[N + 1][B + 1];
	float red[N][B]; //tracks number of redundant machines
	int i, b;

	for (b = 0; b <= B; b++) // for all amounts you spend 
	{
		REL[0][b] = 1.0f; // if you have not run any steps the prob is 1 
	}

	for (i = 1; i <= N; i++) // init the 0 spent colum 
	{
		REL[i][0] = REL[i - 1][0] * rProb[i - 1];
	}

	for (i = 1; i <= N; i++)
	{
		for (b = 1; b <= B; b++)
		{
			int nm = b / Cost[i - 1]; //range to take the maximum over in for loop
			float best = 0;
			red[i - 1][b - 1] = 0;
			for (int mi = 0; mi <= nm; mi++)
			{
				float sp = 1.0f - powf((1.0f - rProb[i - 1]), mi + 1); // step probability  
				int leftover = b - mi * Cost[i - 1];
				float total_prob = REL[i - 1][leftover] * sp; // probability so far 

				if (best < total_prob)
				{
					best = total_prob;
					red[i - 1][b - 1] = mi; // set number of machines used at this stage 
				}
			}
			REL[i][b] = best;
		}
	}

	cout << "\nBudget: " << B << endl;
	cout << "Number of machines: " << N << endl <<endl;

	cout<<"Memoized Version: "<<endl;
        cout<<"Maximum reliability: "<<REL[N][B]<<endl;

	int index  = B - 1; //offset 
	for (i = N-1; i >= 0; i--) 
	{
		out[i] = red[i][index];      // save number of machines 
		int cost = red[i][index] * Cost[i]; //How much did they cost   
		index = index - cost;    //how much do you have left    
	}

	// Print the number of extra machines best employed for each step in the correct order     
	for (i = N-1; i >= 0; i--)
	{
  		cout << out[i] << " copies of machine " << i+1 << " of cost "<<Cost[i]<<endl;
	}

	return 0;
}
