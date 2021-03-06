#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <time.h> 

int main(int argc, char** argv){
    int meuRank, np, origem, destino, tag=0;
    char msg[100];
    
    int N = 100;

    int a[N][N], b[N][N], c[N][N];

    int i, j, k;

    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            a[i][j] = 1;
            b[i][j] = 1;
            c[i][j] = 0;
        }
    }

    clock_t t; 
    t = clock(); 

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meuRank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    for(i = meuRank; i < N; i+=np){
        for(j = 0; j < N; j++){
            for(k = 0; k < N; k++){
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }

    if(meuRank != 0){
        printf("Processo %d está calculando!\n", meuRank);
        destino = 0;
        for(i = meuRank; i < N; i+=np){
            MPI_Send(c[i], N, MPI_INT, destino, tag, MPI_COMM_WORLD);
        }
    }else{
        printf("Processo %d está calculando!\n", meuRank);
        for(origem=1; origem < np; origem++){
            for(i = origem; i < N; i+=np){
                MPI_Recv(c[i], N, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
            }
        }

        t = clock() - t; 
        double tempo = ((double)t)/CLOCKS_PER_SEC;
        printf("gastou %f segundos\n", tempo);

        
    }

    MPI_Finalize();

    return 0;
}
