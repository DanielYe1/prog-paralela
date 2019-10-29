gcc -o soma_matriz.out soma_matriz.c -fopenmp
echo "Execução com 4 threads de soma e multiplicação de matrizes"
export OMP_NUM_THREADS=4
./soma_matriz.out
echo "---------------------------"

gcc omp_integral.c -o omp.out -fopenmp
echo "Execução com 4 threads openMP 1024 trapézios"
export OMP_NUM_THREADS=4
./omp.out

echo "---------------------------"

echo "MPI 4 Processos 1024 trapézios"
mpicc mpi_resto_integral.c -o mpi.out
mpirun -np 4 mpi.out