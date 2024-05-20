#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4  // Define el tamaño maximo de la matriz y el vector

// Función principal
int main(int argc, char *argv[])
{
    int procesador, cantidad;
    int matriz[N][N];
    int vector[N];
    int resultado[N];
    int local_resultado[N];
    int i, j;
    
    MPI_Init(&argc, &argv); // Inicializa el entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &procesador); // Obtiene el rank del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &cantidad); // Obtiene el número de procesos

    // Inicializa la matriz y el vector en el proceso root
    if (procesador == 0) {
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                matriz[i][j] = i * N + j + 1; // Ejemplo de inicialización
            }
            vector[i] = i + 1; // Ejemplo de inicialización
        }
    }

    // Distribuir el vector a todos los procesos
    MPI_Bcast(vector, N, MPI_INT, 0, MPI_COMM_WORLD);

    // Dividir la matriz entre los procesos
    int filas_por_proceso = N / cantidad;
    int local_matriz[filas_por_proceso][N];

    MPI_Scatter(matriz, filas_por_proceso * N, MPI_INT, local_matriz, filas_por_proceso * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Inicializar el resultado local a 0
    for (i = 0; i < filas_por_proceso; i++) {
        local_resultado[i] = 0;
        for (j = 0; j < N; j++) {
            local_resultado[i] += local_matriz[i][j] * vector[j];
        }
    }

    // Recolectar los resultados locales en el proceso root
    MPI_Gather(local_resultado, filas_por_proceso, MPI_INT, resultado, filas_por_proceso, MPI_INT, 0, MPI_COMM_WORLD);

    // El proceso root imprime el resultado
    if (procesador == 0) {
        printf("Resultado de la multiplicación:\n");
        for (i = 0; i < N; i++) {
            printf("%d\n", resultado[i]);
        }
    }

    MPI_Finalize(); // Finaliza el entorno MPI
    return 0;
}
