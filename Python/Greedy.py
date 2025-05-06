import math
import random
import time

# Función para calcular la distancia entre dos puntos
def distancia(p1, p2):
    return math.sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)

# Función para calcular el largo de un recorrido
def largo_recorrido(ruta, puntos):
    total = 0
    for i in range(len(ruta) - 1):
        total += distancia(puntos[ruta[i]], puntos[ruta[i + 1]])
    return total

# Algoritmo Greedy
def algoritmo_greedy(puntos):
    n = len(puntos)
    ruta = [0]  # Empezar desde la primera ciudad
    visitado = [False] * n
    visitado[0] = True

    while len(ruta) < n:
        ciudad_actual = ruta[-1]
        min_distancia = float('inf')
        ciudad_proxima = -1

        # Buscar la ciudad no visitada más cercana
        for i in range(n):
            if not visitado[i] and distancia(puntos[ciudad_actual], puntos[i]) < min_distancia:
                min_distancia = distancia(puntos[ciudad_actual], puntos[i])
                ciudad_proxima = i

        ruta.append(ciudad_proxima)
        visitado[ciudad_proxima] = True

    ruta.append(ruta[0])  # Añadir la ciudad de inicio para cerrar el recorrido

    return ruta, largo_recorrido(ruta, puntos)

# Ejemplo de uso
if __name__ == '__main__':
    # Generación de puntos aleatorios
    puntos = [(random.randint(0, 100), random.randint(0, 100)) for _ in range(10)]

    start_time = time.time()
    mejor_ruta, mejor_largo = algoritmo_greedy(puntos)
    end_time = time.time()

    # Imprimir el resultado
    print("Mejor ruta:", mejor_ruta)
    print("Distancia total:", mejor_largo)
    print("Tiempo de ejecución:", end_time - start_time, "segundos")
