#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

#define SIZE 10
int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE], D[SIZE][SIZE], E[SIZE][SIZE], F[SIZE][SIZE], G[SIZE][SIZE], H[SIZE][SIZE];
int Res[SIZE][SIZE], Res1[SIZE][SIZE], Res2[SIZE][SIZE], Res3[SIZE][SIZE], Res4[SIZE][SIZE];
int main(int argc, char **argv){
	int i, j, k, N;
	N = SIZE;

    clock_t t; 
    t = clock(); 

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			A[i][j] = i+j;
			B[i][j] = i+j;
			C[i][j] = i+j;
			D[i][j] = i+j;
			E[i][j] = i+j;
			F[i][j] = i+j;
			G[i][j] = i+j;
			H[i][j] = i+j;
			Res[i][j] = 0;
			Res1[i][j] = 0;
			Res2[i][j] = 0;
			Res3[i][j] = 0;
			Res4[i][j] = 0;
		}
	}
	//	res = (AxB) + (CXD) + (E+F) + (G+H)

	printf("-------------- Matriz inicializada --------------\n");

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}
	#pragma omp parallel shared(A, B, C, D, E, F, G, H, Res, Res1, Res2, Res3, Res4) private(i, j, k)
	{
		#pragma omp sections
		{
			#pragma omp section 
			{
				#pragma omp parallel private(i,j,k)
				{
				#pragma for
					for (i = 0; i < N; i++)
					{
						for (j = 0; j < N; j++)
						{
							for (k = 0; k < N; k++)
							{
								Res1[i][j] = Res1[i][j] + A[i][k] * B[k][j];
							}
						}
					}
				}
				#pragma omp parallel private(i,j,k) shared(E,F)
				#pragma for
				for (i = 0; i < N; i++)
				{
					for (j = 0; j < N; j++)
					{
						Res2[i][j] = E[i][j] + F[i][j];
					}
				}
				for (i = 0; i < N; i++)
				{
					for (j = 0; j < N; j++)
					{
						#pragma atomic
						Res[i][j] = Res1[i][j] + Res2[i][j] + Res[i][j];
					}
				}
			}
			#pragma omp section 
			{
				#pragma omp parallel private(i,j,k)
				#pragma for
				for (i = 0; i < N; i++)
				{
					for (j = 0; j < N; j++)
					{
						for (k = 0; k < N; k++)
						{
							Res3[i][j] = Res3[i][j] + C[i][k] * D[k][j];
						}
					}
				}
				#pragma omp parallel private(i,j,k)
				#pragma for
				for (i = 0; i < N; i++)
				{
					for (j = 0; j < N; j++)
					{
						Res4[i][j] = G[i][j] + H[i][j];
					}
				}
				for (i = 0; i < N; i++)
				{
					for (j = 0; j < N; j++)
					{
					#pragma atomic
						Res[i][j] = Res3[i][j] + Res4[i][j] + Res[i][j];
					}
				}
			}
		}
	}

    printf("-------------- Matriz Resultado --------------\n");


	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			printf("%d ", Res[i][j]);
		}
		printf("\n");
	}

	t = clock() - t; 
    double tempo = ((double)t)/CLOCKS_PER_SEC;
    printf("gastou %f segundos\n", tempo);
}