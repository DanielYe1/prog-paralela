#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <time.h> 


#define SIZE 100
int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

int main()
{
	int i,j,k,N;
	N = SIZE;
	#pragma omp parallel private(i,j)
	#pragma omp for
	for(i = 0 ; i < SIZE; i++){
		for(j = 0; j < SIZE; j++) {
			A[i][j] = 1;
			B[i][j] = 1;
			C[i][j] = 0;
		}
	}

    clock_t t; 
    t = clock(); 

	#pragma omp parallel shared(A,B,C,N) private(i,j,k)
	#pragma omp for 
	for(i = 0; i < N; i++){
		for( j = 0; j < N; j++) {
			for (k = 0; k < N ; k++) {
				C[i][j] = C[i][j] + A[i][k] * B[k][j];
			}
		}
	}
	
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("fun() took %f seconds to execute \n", time_taken);

	for(i = 0; i < SIZE; i++) {
		for(j = 0; j < SIZE; j++) {
			printf("%d ", C[i][j]);
		}
		printf("\n");
	}

}
