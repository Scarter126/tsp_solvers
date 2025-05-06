# tsp_brute_force.py
import itertools
import time
import math

# Coordenadas fijas de 10 ciudades
cities = [
    (0, 0), (1, 5), (5, 2), (3, 8), (7, 6),
    (8, 3), (6, 1), (2, 2), (4, 7), (9, 5)
]

def distance(a, b):
    return math.hypot(a[0] - b[0], a[1] - b[1])

def total_distance(route):
    return sum(distance(cities[route[i]], cities[route[i+1]]) for i in range(len(route)-1)) + distance(cities[route[-1]], cities[route[0]])

def tsp_brute_force():
    best_dist = float('inf')
    best_route = None
    for perm in itertools.permutations(range(len(cities))):
        dist = total_distance(perm)
        if dist < best_dist:
            best_dist = dist
            best_route = perm
    return best_dist, best_route

start_time = time.time()
dist, route = tsp_brute_force()
end_time = time.time()

print(f"Tiempo de ejecución: {end_time - start_time:.6f} segundos")
