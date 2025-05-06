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

# Enfriamiento cuántico (versión heurística inspirada)
def enfriamiento_cuantico(puntos, n_iteraciones=1000, temperatura_inicial=1000, temperatura_final=0.01, alpha=0.995):
    n = len(puntos)
    mejor_ruta = list(range(n))
    mejor_largo = largo_recorrido(mejor_ruta, puntos)

    ruta = mejor_ruta[:]
    temperatura = temperatura_inicial

    while temperatura > temperatura_final:
        for _ in range(n_iteraciones):
            i, j = random.sample(range(n), 2)  # Elegir dos índices aleatorios
            ruta[i], ruta[j] = ruta[j], ruta[i]  # Intercambiar las posiciones

            largo = largo_recorrido(ruta, puntos)

            if largo < mejor_largo or math.exp((mejor_largo - largo) / temperatura) > random.random():
                mejor_ruta = ruta[:]
                mejor_largo = largo
            else:
                # Si no aceptamos, revertimos el cambio
                ruta[i], ruta[j] = ruta[j], ruta[i]

        temperatura *= alpha

    return mejor_ruta, mejor_largo

# Ejemplo de uso
if __name__ == '__main__':
    # Generación de puntos aleatorios
    puntos = [(random.randint(0, 100), random.randint(0, 100)) for _ in range(10)]

    start_time = time.time()
    mejor_ruta, mejor_largo = enfriamiento_cuantico(puntos)
    end_time = time.time()

    # Imprimir el resultado
    print("Mejor ruta:", mejor_ruta)
    print("Distancia total:", mejor_largo)
    print("Tiempo de ejecución:", end_time - start_time, "segundos")
