#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// Función de distancia
double distancia(pair<int, int> p1, pair<int, int> p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

// Función para calcular el largo de un recorrido
double largo_recorrido(vector<int>& ruta, vector<pair<int, int>>& puntos) {
    double total = 0;
    for (int i = 0; i < ruta.size() - 1; ++i) {
        total += distancia(puntos[ruta[i]], puntos[ruta[i + 1]]);
    }
    return total;
}

// Enfriamiento cuántico (versión heurística inspirada)
pair<vector<int>, double> enfriamiento_cuantico(vector<pair<int, int>>& puntos, int n_iteraciones = 1000, double temperatura_inicial = 1000, double temperatura_final = 0.01, double alpha = 0.995) {
    int n = puntos.size();
    vector<int> mejor_ruta(n);
    for (int i = 0; i < n; ++i) mejor_ruta[i] = i;
    double mejor_largo = largo_recorrido(mejor_ruta, puntos);

    vector<int> ruta = mejor_ruta;
    double temperatura = temperatura_inicial;

    while (temperatura > temperatura_final) {
        for (int iter = 0; iter < n_iteraciones; ++iter) {
            // Realizamos un intercambio de dos ciudades aleatorias
            int i = rand() % n;
            int j = rand() % n;
            swap(ruta[i], ruta[j]);

            // Calculamos el largo de la nueva ruta
            double largo = largo_recorrido(ruta, puntos);

            // Si la nueva ruta es mejor, la aceptamos, si no, con cierta probabilidad
            if (largo < mejor_largo || exp((mejor_largo - largo) / temperatura) > (rand() / double(RAND_MAX))) {
                mejor_ruta = ruta;
                mejor_largo = largo;
            } else {
                // Si no la aceptamos, revertimos el intercambio
                swap(ruta[i], ruta[j]);
            }
        }

        // Reducir la temperatura
        temperatura *= alpha;
    }

    return make_pair(mejor_ruta, mejor_largo);
}

// Ejemplo de uso
int main() {
    srand(time(0));

    // Generación de puntos aleatorios (por ejemplo, 10 puntos)
    vector<pair<int, int>> puntos;
    for (int i = 0; i < 10; ++i) {
        puntos.push_back({rand() % 100, rand() % 100});
    }

    clock_t start_time = clock();

    // Llamar al algoritmo de Enfriamiento Cuántico
    pair<vector<int>, double> resultado = enfriamiento_cuantico(puntos);

    vector<int> mejor_ruta = resultado.first;
    double mejor_largo = resultado.second;

    clock_t end_time = clock();

    // Imprimir el resultado
    cout << "Mejor ruta:";
    for (int i : mejor_ruta) {
        cout << " " << i;
    }
    cout << "\nDistancia total: " << mejor_largo << endl;
    cout << "Tiempo de ejecución: " << double(end_time - start_time) / CLOCKS_PER_SEC << " segundos\n";
}
