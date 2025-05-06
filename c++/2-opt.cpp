// tsp_2opt.cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

vector<pair<double, double>> cities = {
    {0, 0}, {1, 5}, {5, 2}, {3, 8}, {7, 6},
    {8, 3}, {6, 1}, {2, 2}, {4, 7}, {9, 5}
};

double distance(pair<double, double> a, pair<double, double> b) {
    return hypot(a.first - b.first, a.second - b.second);
}

double total_distance(const vector<int>& route) {
    double dist = 0;
    for (size_t i = 0; i < route.size() - 1; i++)
        dist += distance(cities[route[i]], cities[route[i + 1]]);
    dist += distance(cities[route.back()], cities[route[0]]);
    return dist;
}

vector<int> two_opt(vector<int> route) {
    bool improved = true;
    while (improved) {
        improved = false;
        for (size_t i = 1; i < route.size() - 2; i++) {
            for (size_t j = i + 1; j < route.size(); j++) {
                if (j - i == 1) continue;
                vector<int> new_route = route;
                reverse(new_route.begin() + i, new_route.begin() + j);
                if (total_distance(new_route) < total_distance(route)) {
                    route = new_route;
                    improved = true;
                }
            }
        }
    }
    return route;
}

int main() {
    vector<int> route;
    for (int i = 0; i < cities.size(); i++) route.push_back(i);
    shuffle(route.begin(), route.end(), default_random_engine(time(0)));

    auto start = high_resolution_clock::now();
    vector<int> best_route = two_opt(route);
    auto end = high_resolution_clock::now();

    duration<double> elapsed = end - start;
    cout << "Tiempo de ejecución: " << elapsed.count() << " segundos" << endl;
    return 0;
}
