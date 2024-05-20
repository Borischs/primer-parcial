#include <stdio.h>
#include <mpi.h>

// Función para calcular el término de Fibonacci
int fibonacci(int n)
{
    if (n < 2)
        return n;
    else
        return fibonacci(n - 2) + fibonacci(n - 1);
}

int main(int argc, char *argv[])
{
    int procesador, cantidad;
    int n = 30; // Número de términos de la secuencia de Fibonacci

    MPI_Init(&argc, &argv); // Inicializa el entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &procesador); // Obtiene el rank del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &cantidad); // Obtiene el número total de procesos

    if (procesador == 0) {
        // Proceso MASTER
        printf("Secuencia de Fibonacci:\n");
        for (int i = 0; i < n; i++) {
            int vrecepcion;
            MPI_Recv(&vrecepcion, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%d ", vrecepcion);
        }
        printf("\n");
    } else {
        // Proceso SLAVE
        for (int i = 0; i < n; i++) {
            int venvio = fibonacci(i);
            MPI_Send(&venvio, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize(); // Finaliza el entorno MPI
    return 0;
}
