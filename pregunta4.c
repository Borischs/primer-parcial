#include <stdio.h>
#include <omp.h>

#define MAX_N 100 // Define el tamaño maximo

// Función para multiplicar una matriz NxN con un vector de dimensión N
void multiplicarMatrizVector(int matriz[MAX_N][MAX_N], int vector[MAX_N], int resultado[MAX_N], int N)
{
    // Inicializar el vector resultado
    for(int i = 0; i < N; i++)
    {
        resultado[i] = 0;
    }

    // Multiplicación paralela utilizando OpenMP
    #pragma omp parallel for
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            #pragma omp atomic
            resultado[i] += matriz[i][j] * vector[j];
        }
    }
}

void main()
{
    int N;
    int matriz[MAX_N][MAX_N];
    int vector[MAX_N];
    int resultado[MAX_N];
    int i, j;
    printf("Ingrese el valor de N (max %d): ", MAX_N);
    scanf("%d", &N);
    //validar N
    if (N>MAX_N)
    {
        printf("El tamaño maximo permitido es %d.\n", MAX_N);
        return;
    }

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
              matriz[i][j] = i * N + j + 1; 
        }
        vector[i] = i + 1; 
    }


    // Llamar a la función de multiplicación
    multiplicarMatrizVector(matriz, vector, resultado, N);

    // Imprimir el resultado
    printf("Resultado de la multiplicación:\n");
    for(int i = 0; i < N; i++)
    {
        printf("%d\n", resultado[i]);
    }
    
}
