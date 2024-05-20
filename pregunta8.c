#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 1000  // Define un valor máximo para los términos

int main(int argc, char *argv[])
{
    int N = 100; // Número de términos
    int M;       // Número de procesadores (threads)
    
    // Lee el número de threads desde la entrada
    if (argc > 1)
    {
        M = atoi(argv[1]);
    } 
    else
    {
        M = omp_get_max_threads(); // Usa el máximo número de threads disponibles por defecto
    }

    int serie[MAX_TERMS];

    // Establece el número de threads a usar
    omp_set_num_threads(M);

    // Paraleliza la generación de la serie
    #pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        serie[i] = 2 * (i + 1);
    }

    // Imprime la serie
    printf("Serie generada:\n");
    for (int i = 0; i < N; i++)
    {
        printf("%d ", serie[i]);
    }
    printf("\n");

    return 0;
}
