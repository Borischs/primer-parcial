#include <iostream>

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

void main()
{
    float num1, num2;
    std::cout << "Ingrese el primer número: ";
    std::cin >> num1;
    std::cout << "Ingrese el segundo número: ";
    std::cin >> num2;

    std::cout << "Suma: " << suma(&num1, &num2) << std::endl;
    std::cout << "Resta: " << resta(&num1, &num2) << std::endl;
    std::cout << "Multiplicación: " << multiplicacion(&num1, &num2) << std::endl;
    std::cout << "División: " << division(&num1, &num2) << std::endl;
}
