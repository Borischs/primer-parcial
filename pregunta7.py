import multiprocessing
import math

def f(x):
    return 4.0 / (1.0 + x * x)

def calcular_pi_seccion(inicio, parar, h):
    suma_local = 0.0
    for i in range(inicio, parar):
        x = h * (i - 0.5)
        suma_local += f(x)
    return suma_local

def main():
    num_intervalos = 1000000 # Número total de intervalos para la integración.
    num_procesos = multiprocessing.cpu_count() # Número de procesos, igual al número de núcleos de CPU disponibles.
    h = 1.0 / num_intervalos
    tam_bloq = num_intervalos // num_procesos # Tamaño del bloque de intervalos que manejará cada proceso.

    with multiprocessing.Pool(processes=num_procesos) as pool:
        results = [
            pool.apply_async(calcular_pi_seccion, (i * tam_bloq + 1, (i + 1) * tam_bloq + 1, h))
            for i in range(num_procesos)
        ]

        total_sum = sum(result.get() for result in results)

    pi = h * total_sum
    print(f"El valor aproximado de PI es: {pi:.15f}")

if __name__ == "__main__":
    main()