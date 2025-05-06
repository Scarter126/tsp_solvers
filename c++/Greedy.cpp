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

// Algoritmo Greedy
pair<vector<int>, double> algoritmo_greedy(vector<pair<int, int>>& puntos) {
    int n = puntos.size();
    vector<int> ruta;
    vector<bool> visitado(n, false);

    // Empezar desde la primera ciudad
    ruta.push_back(0);
    visitado[0] = true;

    while (ruta.size() < n) {
        int ciudad_actual = ruta.back();
        double min_distancia = numeric_limits<double>::infinity();
        int ciudad_proxima = -1;

        // Buscar la ciudad no visitada más cercana
        for (int i = 0; i < n; ++i) {
            if (!visitado[i] && distancia(puntos[ciudad_actual], puntos[i]) < min_distancia) {
                min_distancia = distancia(puntos[ciudad_actual], puntos[i]);
                ciudad_proxima = i;
            }
        }

        // Añadir la ciudad más cercana
        ruta.push_back(ciudad_proxima);
        visitado[ciudad_proxima] = true;
    }

    // Añadir la ciudad de inicio al final para cerrar el recorrido
    ruta.push_back(ruta[0]);

    return make_pair(ruta, largo_recorrido(ruta, puntos));
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

    // Llamar al algoritmo Greedy
    pair<vector<int>, double> resultado = algoritmo_greedy(puntos);

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
