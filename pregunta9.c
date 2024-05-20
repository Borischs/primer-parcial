#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) 
{
    int procesador, cantidad;
    int N = 100; // Número de términos
    int M;       // Número de procesos (vectores)

    MPI_Init(&argc, &argv); // Inicializa el entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &procesador); // Obtiene el rank del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &cantidad); // Obtiene el número total de procesos

    M = cantidad; // Cada proceso es un vector

    int terms_por_proceso = N / M;
    int inicio_term = procesador * terms_por_proceso + 1;
    int fin_term = inicio_term + terms_por_proceso - 1;

    if (procesador == M - 1)
    {
        // Asegura que el último proceso tome los términos adicionales si N no es divisible por M
        fin_term = N;
    }

    printf("Proceso %d generando términos desde %d hasta %d\n", procesador, inicio_term, fin_term);

    // Genera la serie
    for (int i = inicio_term; i <= fin_term; i++)
    {
        printf("%d ", 2 * i);
    }
    printf("\n");

    MPI_Finalize(); // Finaliza el entorno MPI
    return 0;
}
