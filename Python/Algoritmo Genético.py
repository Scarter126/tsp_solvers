import random
import time


# Función para calcular la distancia entre dos puntos
def distancia(p1, p2):
    return ((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2) ** 0.5


# Función para calcular el largo de un recorrido
def largo_recorrido(ruta, puntos):
    return sum(distancia(puntos[ruta[i]], puntos[ruta[i + 1]]) for i in range(len(ruta) - 1))


# Operador de cruce (crossover)
def cruce(padre1, padre2):
    start, end = sorted(random.sample(range(len(padre1)), 2))
    hijo = [-1] * len(padre1)
    hijo[start:end + 1] = padre1[start:end + 1]

    idx = 0
    for i in range(len(padre2)):
        if padre2[i] not in hijo:
            while hijo[idx] != -1:
                idx += 1
            hijo[idx] = padre2[i]

    return hijo


# Algoritmo Genético
def algoritmo_genetico(puntos, n_generaciones=500, n_poblacion=100, tasa_mutacion=0.1):
    poblacion = [random.sample(range(len(puntos)), len(puntos)) for _ in range(n_poblacion)]

    for _ in range(n_generaciones):
        poblacion = sorted(poblacion, key=lambda ruta: largo_recorrido(ruta, puntos))
        nueva_poblacion = poblacion[:2]  # Seleccionamos los dos mejores

        while len(nueva_poblacion) < n_poblacion:
            padre1, padre2 = random.sample(poblacion[:n_poblacion // 2], 2)
            hijo = cruce(padre1, padre2)
            if random.random() < tasa_mutacion:
                i, j = random.sample(range(len(hijo)), 2)
                hijo[i], hijo[j] = hijo[j], hijo[i]
            nueva_poblacion.append(hijo)

        poblacion = nueva_poblacion

    mejor_ruta = min(poblacion, key=lambda ruta: largo_recorrido(ruta, puntos))
    return mejor_ruta, largo_recorrido(mejor_ruta, puntos)


# Ejemplo de uso
if __name__ == "__main__":
    puntos = [(random.randint(0, 100), random.randint(0, 100)) for _ in range(10)]

    start_time = time.time()
    mejor_ruta, mejor_largo = algoritmo_genetico(puntos)
    end_time = time.time()

    print("Mejor ruta:", mejor_ruta)
    print("Distancia total:", mejor_largo)
    print("Tiempo de ejecución:", end_time - start_time, "segundos")
