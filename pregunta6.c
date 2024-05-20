#include <mpi.h>
#include <stdio.h>
#include <math.h>

double f(double x) {
    return 4.0 / (1.0 + x * x);
}

int main(int argc, char *argv[]) {
    int procesador, cantidad;
    int num_intervalos = 1000000; // Número de intervalos
    double h, x, local_sum, global_sum;
    
    MPI_Init(&argc, &argv); // Inicializa el entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &procesador); // Obtiene el rank del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &cantidad); // Obtiene el número de procesos

    h = 1.0 / num_intervalos;
    local_sum = 0.0;

    // Cada proceso calcula su parte del intervalo
    for (int i = procesador + 1; i <= num_intervalos; i += cantidad) {
        x = h * (i - 0.5);
        local_sum += f(x);
    }

    // Suma las partes calculadas por cada proceso
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // El proceso root imprime el resultado
    if (procesador == 0) {
        double pi = h * global_sum;
        printf("El valor aproximado de PI es: %.15f\n", pi);
    }

    MPI_Finalize(); // Finaliza el entorno MPI
    return 0;
}
