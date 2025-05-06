#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>  // Para std::find, std::iota, std::shuffle, std::sort
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

// Operador de cruce (crossover)
vector<int> cruce(const vector<int>& padre1, const vector<int>& padre2) {
    size_t start = rand() % padre1.size();
    size_t end = rand() % padre1.size();
    if (start > end) swap(start, end);

    vector<int> hijo(padre1.size(), -1);
    for (size_t i = start; i <= end; ++i) {
        hijo[i] = padre1[i];
    }

    size_t idx = 0;
    for (size_t i = 0; i < padre2.size(); ++i) {
        if (find(hijo.begin(), hijo.end(), padre2[i]) == hijo.end()) {
            while (hijo[idx] != -1) idx++;
            hijo[idx] = padre2[i];
        }
    }

    return hijo;
}

// Algoritmo Genético
pair<vector<int>, double> algoritmo_genetico(vector<pair<int, int>>& puntos, int n_generaciones = 500, int n_poblacion = 100, double tasa_mutacion = 0.1) {
    vector<vector<int>> poblacion;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, puntos.size() - 1);

    // Inicialización de la población
    for (int i = 0; i < n_poblacion; ++i) {
        vector<int> individuo(puntos.size());
        iota(individuo.begin(), individuo.end(), 0);
        shuffle(individuo.begin(), individuo.end(), gen);
        poblacion.push_back(individuo);
    }

    vector<int> mejor_ruta;
    double mejor_largo = numeric_limits<double>::infinity();

    for (int g = 0; g < n_generaciones; ++g) {
        // Ordenar la población por el largo del recorrido
        sort(poblacion.begin(), poblacion.end(), [&puntos](const vector<int>& a, const vector<int>& b) {
            return largo_recorrido(a, puntos) < largo_recorrido(b, puntos);
        });

        vector<vector<int>> nueva_poblacion(poblacion.begin(), poblacion.begin() + 2);

        while (nueva_poblacion.size() < n_poblacion) {
            int i = rand() % (n_poblacion / 2);
            int j = rand() % (n_poblacion / 2);
            vector<int> hijo = cruce(poblacion[i], poblacion[j]);
            if ((rand() % 100) < tasa_mutacion * 100) {
                swap(hijo[rand() % puntos.size()], hijo[rand() % puntos.size()]);
            }
            nueva_poblacion.push_back(hijo);
        }

        poblacion = nueva_poblacion;

        // Evaluar la mejor ruta en la población
        for (const auto& ruta : poblacion) {
            double largo = largo_recorrido(ruta, puntos);
            if (largo < mejor_largo) {
                mejor_largo = largo;
                mejor_ruta = ruta;
            }
        }
    }

    return make_pair(mejor_ruta, mejor_largo);
}

int main() {
    srand(time(0));

    vector<pair<int, int>> puntos;
    for (int i = 0; i < 10; ++i) {
        puntos.push_back({rand() % 100, rand() % 100});
    }

    clock_t start_time = clock();

    // Uso tradicional de 'first' y 'second' para obtener los resultados del pair
    pair<vector<int>, double> resultado = algoritmo_genetico(puntos);
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
