#include <stdio.h>

// Función para sumar dos números
float suma(float *a, float *b)
{
    return *a + *b;
}

// Función para restar dos números
float resta(float *a, float *b)
{
    return *a - *b;
}

// Función para multiplicar dos números (basada en sumas)
float multiplicacion(float *a, float *b)
{
    float result = 0;
    for (int i = 0; i < *b; i++) {
        result += *a;
    }
    return result;
}

// Función para dividir dos números (basada en restas)
float division(float *a, float *b)
{
    float result = 0;
    float temp = *a;
    while (temp >= *b) {
        temp -= *b;
        result++;
    }
    return result;
}

void main() {
    float num1, num2;
    printf("Ingrese el primer número: ");
    scanf("%f", &num1);
    printf("Ingrese el segundo número: ");
    scanf("%f", &num2);

    printf("Suma: %.2f\n", suma(&num1, &num2));
    printf("Resta: %.2f\n", resta(&num1, &num2));
    printf("Multiplicación: %.2f\n", multiplicacion(&num1, &num2));
    printf("División: %.2f\n", division(&num1, &num2));
}