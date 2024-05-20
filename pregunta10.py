import multiprocessing

def generar_serie(inicio, fin):
    serie = []
    for i in range(inicio, fin + 1):
        serie.append(2 * i)
    return serie

def main():
    N = 100  # Número de términos
    M = 4    # Número de procesos (vectores)

    # Calcula cuántos términos generará cada proceso
    terms_por_proceso = N // M

    # Calcula los límites de los términos para cada proceso
    ranges = [(i * terms_por_proceso + 1, (i + 1) * terms_por_proceso) for i in range(M)]

    # Asegura que el último proceso tome los términos adicionales si N no es divisible por M
    ranges[-1] = (ranges[-1][0], N)

    # Crea un pool de procesos
    with multiprocessing.Pool(processes=M) as pool:
        # Genera la serie en paralelo
        results = pool.starmap(generar_serie, ranges)

    # Imprime la serie generada por cada proceso
    for i, result in enumerate(results):
        print(f"Proceso {i}: {result}")

if __name__ == "__main__":
    main()