#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <gmp.h>

#define PRECISION 25

int rank, size;

int main(int argc, char* argv[]){

    // File with the numbers found.
    FILE* result;

    // Declaracion de variables.
    mpz_t fibo, last, penlt;

    // Attribution of variables.
    mpz_init_set_str(fibo, "1", 10);
    mpz_init_set_str(last, "1", 10);
    mpz_init_set_str(penlt, "1", 10);

    // Nth Fibonacci .
    int n_fib = 0;

    // Start of parallel execution.
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    while(1){

        // Encontrando el sgte nro fibo.
        mpz_add(fibo, last, penlt);
        mpz_set(penlt, last);
        mpz_set(last, fibo);

        // Choose a thread to check if the Fibonacci number is prime.
        if((n_fib % size) == rank){

            
            if(mpz_probab_prime_p(fibo, PRECISION)){

               
                system("DAY=$(date +%c) && echo [$DAY] >> result_file");

              
                result = fopen("result_file", "a");
                mpz_out_str(result, 10, fibo);
                fputs("\n\n", result);
                fclose(result);

            }

        }

        n_fib++;

    }

    // End of parallel execution.
    MPI_Finalize();

}
