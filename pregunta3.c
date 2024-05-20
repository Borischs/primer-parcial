#include <stdio.h>
#include <omp.h>

// Función para multiplicar dos números usando sumas repetidas con OpenMP
int multiplicacion(int a, int b)
{
    int resultado = 0;

    #pragma omp parallel for reduction(+:resultado)
    for(int i = 0; i < b; i++) {
        resultado += a;
    }
    return resultado;
}

// Función para dividir dos números usando restas repetidas con OpenMP
int division(int a, int b) 
{
    int resultado = 0;
    int temp = a;

    #pragma omp parallel
    {
        int local_result = 0;

        #pragma omp for
        for(int i = 0; i < a; i++) {
            if(temp >= b) {
                temp -= b;
                local_result++;
            }
        }

        #pragma omp critical
        resultado += local_result;
    }
    return resultado;
}

void main()
{
    int a, b;
    int resultado_m, resultado_d;
    printf("Ingrese el primer número: ");
    scanf("%d", &a);
    printf("Ingrese el segundo número: ");
    scanf("%d", &b);

    resultado_m = multiplicacion(a, b);
    printf("Multiplicación: %d * %d = %d\n", a, b, resultado_m);

    resultado_d = division(a, b);
    printf("División: %d / %d = %d\n", a, b, resultado_d);
}
