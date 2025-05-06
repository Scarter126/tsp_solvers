#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
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

// Función para elegir un índice aleatorio basado en probabilidades
int random_choice(const vector<double>& probabilidades) {
    double r = (rand() / double(RAND_MAX));  // Número aleatorio entre 0 y 1
    double acumulado = 0;

    for (int i = 0; i < probabilidades.size(); ++i) {
        acumulado += probabilidades[i];
        if (r < acumulado) {
            return i;
        }
    }

    return probabilidades.size() - 1;  // En caso de que no se elija ninguna (muy improbable)
}

// Algoritmo de Colonia de Hormigas
pair<vector<int>, double> colonia_hormigas(vector<pair<int, int>>& puntos, int n_hormigas = 50, int n_iteraciones = 100, double alpha = 1, double beta = 1, double rho = 0.1, double q0 = 0.9) {
    int n = puntos.size();
    vector<vector<double>> feromonas(n, vector<double>(n, 1.0)); // Feromonas iniciales
    vector<int> mejor_ruta;
    double mejor_largo = numeric_limits<double>::infinity();

    for (int iter = 0; iter < n_iteraciones; ++iter) {
        vector<vector<int>> rutas;
        vector<double> largos;

        for (int h = 0; h < n_hormigas; ++h) {
            vector<int> ruta;
            ruta.push_back(rand() % n); // Empezamos con una ciudad aleatoria
            while (ruta.size() < n) {
                int ciudad_actual = ruta.back();
                vector<double> probabilidades(n, 0);

                // Calcular probabilidades de elegir cada ciudad
                for (int ciudad = 0; ciudad < n; ++ciudad) {
                    if (find(ruta.begin(), ruta.end(), ciudad) == ruta.end()) {
                        probabilidades[ciudad] = pow(feromonas[ciudad_actual][ciudad], alpha) * pow(1.0 / distancia(puntos[ciudad_actual], puntos[ciudad]), beta);
                    }
                }

                // Normalizar probabilidades
                double suma_prob = 0;
                for (double p : probabilidades) {
                    suma_prob += p;
                }
                for (double &p : probabilidades) {
                    p /= suma_prob;
                }

                // Selección de ciudad basada en la probabilidad
                int ciudad_elegida;
                if ((rand() / double(RAND_MAX)) < q0) {
                    ciudad_elegida = max_element(probabilidades.begin(), probabilidades.end()) - probabilidades.begin();
                } else {
                    ciudad_elegida = random_choice(probabilidades);
                }

                ruta.push_back(ciudad_elegida);
            }

            // Calcular el largo de la ruta
            double largo = largo_recorrido(ruta, puntos);
            rutas.push_back(ruta);
            largos.push_back(largo);

            // Actualizar mejor ruta
            if (largo < mejor_largo) {
                mejor_largo = largo;
                mejor_ruta = ruta;
            }
        }

        // Actualizar feromonas
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                feromonas[i][j] = (1 - rho) * feromonas[i][j];  // Evaporación
            }
        }

        // Depósito de feromonas basado en la calidad de las rutas
        for (int h = 0; h < n_hormigas; ++h) {
            for (int i = 0; i < n - 1; ++i) {
                int ciudad1 = rutas[h][i];
                int ciudad2 = rutas[h][i + 1];
                double delta = 1.0 / largos[h];
                feromonas[ciudad1][ciudad2] += delta;
                feromonas[ciudad2][ciudad1] += delta;  // El recorrido es bidireccional
            }
        }
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

    // Llamar al algoritmo de Colonia de Hormigas
    pair<vector<int>, double> resultado = colonia_hormigas(puntos);

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
