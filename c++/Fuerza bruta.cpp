// tsp_brute_force.cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

vector<pair<double, double>> cities = {
    {0, 0}, {1, 5}, {5, 2}, {3, 8}, {7, 6},
    {8, 3}, {6, 1}, {2, 2}, {4, 7}, {9, 5}
};

double distance(pair<double, double> a, pair<double, double> b) {
    return hypot(a.first - b.first, a.second - b.second);
}

double total_distance(const vector<int>& route) {
    double dist = 0;
    for (int i = 0; i < route.size() - 1; i++)
        dist += distance(cities[route[i]], cities[route[i+1]]);
    dist += distance(cities[route.back()], cities[route[0]]);
    return dist;
}

int main() {
    vector<int> route;
    for (int i = 0; i < cities.size(); i++) route.push_back(i);

    double best_dist = 1e9;
    vector<int> best_route;

    auto start = high_resolution_clock::now();

    do {
        double d = total_distance(route);
        if (d < best_dist) {
            best_dist = d;
            best_route = route;
        }
    } while (next_permutation(route.begin(), route.end()));

    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;

    cout << "Tiempo de ejecución: " << elapsed.count() << " segundos" << endl;
    return 0;
}
