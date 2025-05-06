import random
import time
import math


# Función de distancia
def distancia(p1, p2):
    return ((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2) ** 0.5


# Función para calcular el largo de un recorrido
def largo_recorrido(ruta, puntos):
    return sum(distancia(puntos[ruta[i]], puntos[ruta[i + 1]]) for i in range(len(ruta) - 1))


# Recocido Simulado
def recocido_simulado(puntos, temperatura_inicial=1000, temperatura_final=1, tasa_enfriamiento=0.995):
    ruta_actual = list(range(len(puntos)))
    random.shuffle(ruta_actual)
    mejor_ruta = ruta_actual[:]
    mejor_largo = largo_recorrido(mejor_ruta, puntos)

    temperatura = temperatura_inicial

    while temperatura > temperatura_final:
        nueva_ruta = ruta_actual[:]
        i, j = random.sample(range(len(puntos)), 2)
        nueva_ruta[i], nueva_ruta[j] = nueva_ruta[j], nueva_ruta[i]

        largo_actual = largo_recorrido(ruta_actual, puntos)
        largo_nueva = largo_recorrido(nueva_ruta, puntos)

        if largo_nueva < largo_actual or random.random() < math.exp((largo_actual - largo_nueva) / temperatura):
            ruta_actual = nueva_ruta

        if largo_nueva < mejor_largo:
            mejor_ruta = nueva_ruta
            mejor_largo = largo_nueva

        temperatura *= tasa_enfriamiento

    return mejor_ruta, mejor_largo


# Ejemplo de uso
if __name__ == "__main__":
    puntos = [(random.randint(0, 100), random.randint(0, 100)) for _ in range(10)]

    start_time = time.time()
    mejor_ruta, mejor_largo = recocido_simulado(puntos)
    end_time = time.time()

    print("Mejor ruta:", mejor_ruta)
    print("Distancia total:", mejor_largo)
    print("Tiempo de ejecución:", end_time - start_time, "segundos")
