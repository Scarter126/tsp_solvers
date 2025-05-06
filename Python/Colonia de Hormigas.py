import random
import time
import numpy as np


# Función de distancia
def distancia(p1, p2):
    return ((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2) ** 0.5


# Función para calcular el largo de un recorrido
def largo_recorrido(ruta, puntos):
    return sum(distancia(puntos[ruta[i]], puntos[ruta[i + 1]]) for i in range(len(ruta) - 1))


# Algoritmo de Colonia de Hormigas
def colonia_hormigas(puntos, n_hormigas=50, n_iteraciones=100, alpha=1, beta=1, rho=0.1, q0=0.9):
    n = len(puntos)
    feromonas = np.ones((n, n))  # Feromonas iniciales
    mejor_ruta = None
    mejor_largo = float('inf')

    for _ in range(n_iteraciones):
        rutas = []
        largos = []

        for _ in range(n_hormigas):
            ruta = [random.randint(0, n - 1)]  # Empezamos con una ciudad aleatoria
            while len(ruta) < n:
                ciudad_actual = ruta[-1]
                probabilidades = []

                for ciudad in range(n):
                    if ciudad not in ruta:
                        prob = (feromonas[ciudad_actual][ciudad] ** alpha) * (
                                    (1 / distancia(puntos[ciudad_actual], puntos[ciudad])) ** beta)
                        probabilidades.append(prob)
                    else:
                        probabilidades.append(0)

                suma_prob = sum(probabilidades)
                probabilidades = [p / suma_prob for p in probabilidades]

                # Selección de ciudad
                if random.random() < q0:
                    ciudad_elegida = probabilidades.index(max(probabilidades))
                else:
                    ciudad_elegida = random.choices(range(n), probabilidades)[0]

                ruta.append(ciudad_elegida)

            largo = largo_recorrido(ruta, puntos)
            rutas.append(ruta)
            largos.append(largo)

            # Actualizar mejor solución
            if largo < mejor_largo:
                mejor_largo = largo
                mejor_ruta = ruta

        # Actualizar feromonas
        feromonas = (1 - rho) * feromonas  # Evaporación de feromonas
        for ruta, largo in zip(rutas, largos):
            for i in range(n - 1):
                feromonas[ruta[i]][ruta[i + 1]] += 1 / largo
                feromonas[ruta[i + 1]][ruta[i]] += 1 / largo  # Porque el recorrido es bidireccional

    return mejor_ruta, mejor_largo


# Ejemplo de uso
if __name__ == "__main__":
    puntos = [(random.randint(0, 100), random.randint(0, 100)) for _ in range(10)]
    start_time = time.time()

    mejor_ruta, mejor_largo = colonia_hormigas(puntos)

    end_time = time.time()

    print("Mejor ruta:", mejor_ruta)
    print("Distancia total:", mejor_largo)
    print("Tiempo de ejecución:", end_time - start_time, "segundos")
