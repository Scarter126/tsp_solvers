#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>  // Para std::find, std::iota, std::shuffle
#include <numeric>    // Para iota
#include <random>     // Para random_device, mt19937, uniform_int_distribution
#include <limits>     // Para numeric_limits

using namespace std;

// Función de distancia
double distancia(pair<int, int> p1, pair<int, int> p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

// Función para calcular el largo de un recorrido
double largo_recorrido(const vector<int>& ruta, const vector<pair<int, int>>& puntos) {
    double total = 0;
    for (size_t i = 0; i < ruta.size() - 1; ++i) {
        total += distancia(puntos[ruta[i]], puntos[ruta[i + 1]]);
    }
    return total;
}

// Recocido Simulado
pair<vector<int>, double> recocido_simulado(vector<pair<int, int>>& puntos, double temperatura_inicial = 1000, double temperatura_final = 1, double tasa_enfriamiento = 0.995) {
    vector<int> ruta_actual(puntos.size());
    iota(ruta_actual.begin(), ruta_actual.end(), 0);  // Inicializar la ruta con los índices de los puntos
    random_device rd;
    mt19937 gen(rd());
    shuffle(ruta_actual.begin(), ruta_actual.end(), gen);  // Mezclar la ruta aleatoriamente

    vector<int> mejor_ruta = ruta_actual;
    double mejor_largo = largo_recorrido(mejor_ruta, puntos);
    double temperatura = temperatura_inicial;

    while (temperatura > temperatura_final) {
        vector<int> nueva_ruta = ruta_actual;
        int i = rand() % puntos.size();
        int j = rand() % puntos.size();
        swap(nueva_ruta[i], nueva_ruta[j]);  // Intercambiar dos elementos en la ruta

        double largo_actual = largo_recorrido(ruta_actual, puntos);
        double largo_nueva = largo_recorrido(nueva_ruta, puntos);

        if (largo_nueva < largo_actual || rand() / double(RAND_MAX) < exp((largo_actual - largo_nueva) / temperatura)) {
            ruta_actual = nueva_ruta;
        }

        if (largo_nueva < mejor_largo) {
            mejor_ruta = nueva_ruta;
            mejor_largo = largo_nueva;
        }

        temperatura *= tasa_enfriamiento;
    }

    return make_pair(mejor_ruta, mejor_largo);
}

int main() {
    srand(time(0));

    vector<pair<int, int>> puntos;
    for (int i = 0; i < 10; ++i) {
        puntos.push_back({rand() % 100, rand() % 100});  // Generar puntos aleatorios
    }

    clock_t start_time = clock();

    // Usar 'first' y 'second' para acceder al 'pair'
    pair<vector<int>, double> resultado = recocido_simulado(puntos);
    vector<int> mejor_ruta = resultado.first;
    double mejor_largo = resultado.second;

    clock_t end_time = clock();

    cout << "Mejor ruta:";
    for (int i : mejor_ruta) {
        cout << " " << i;
    }
    cout << "\nDistancia total: " << mejor_largo << "\n";
    cout << "Tiempo de ejecución: " << double(end_time - start_time) / CLOCKS_PER_SEC << " segundos\n";
}
