# tsp_2opt.py
import time
import math
import random

cities = [
    (0, 0), (1, 5), (5, 2), (3, 8), (7, 6),
    (8, 3), (6, 1), (2, 2), (4, 7), (9, 5)
]

def distance(a, b):
    return math.hypot(a[0] - b[0], a[1] - b[1])

def total_distance(route):
    return sum(distance(cities[route[i]], cities[route[i + 1]]) for i in range(len(route) - 1)) + distance(cities[route[-1]], cities[route[0]])

def two_opt(route):
    best = route
    improved = True
    while improved:
        improved = False
        for i in range(1, len(route) - 2):
            for j in range(i + 1, len(route)):
                if j - i == 1: continue
                new_route = best[:i] + best[i:j][::-1] + best[j:]
                if total_distance(new_route) < total_distance(best):
                    best = new_route
                    improved = True
        route = best
    return best

start_time = time.time()
initial_route = list(range(len(cities)))
random.shuffle(initial_route)
best_route = two_opt(initial_route)
end_time = time.time()

print(f"Tiempo de ejecución: {end_time - start_time:.6f} segundos")
