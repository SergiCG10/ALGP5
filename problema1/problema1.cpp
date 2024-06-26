#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Definir infinito como un valor muy grande
const int INF = numeric_limits<int>::max();

// Función para imprimir la matriz de distancias
void printMatrix(const vector<vector<int>>& dist) {
    int n = dist.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << " " << dist[i][j] << "  ";
        }
        cout << endl;
    }
}

// Función para recuperar el camino más corto entre dos nodos
void getPath(int i, int f, const vector<vector<int>>& next, vector<int>& path) {

    int n = next.size();
    if (i < 0 || i >= n || f < 0 || f >= n) {
        throw out_of_range("Las paradas inicial o final están fuera de los límites del rio.");
    }
    
    if (next[i][f] == -1) {
        cout << "No hay manera de llegar de un pueblo a otro \n";
        return;
    }
    path.push_back(i);
    while (i != f) {
        i = next[i][f];
        path.push_back(i);
    }
}

// Implementación del algoritmo de Floyd-Warshall
void floydWarshall(const vector<vector<int>>& c, vector<vector<int>>& dist, vector<vector<int>>& next) {
    int n = c.size();
    dist = c;
    next.resize(n, vector<int>(n, -1));

    // Inicializar la matriz de predecesores
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (c[i][j] != INF && i != j) {
                next[i][j] = j;
            }
        }
    }

    // Aplicar el algoritmo de Floyd-Warshall
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
    }
}

int main() {
    // Definir la matriz de costes
    
    vector<vector<int>> c = {
        {0, 3, 3, INF, INF},
        {INF, 0, 4, 7, INF},
        {INF, INF, 0, 2, 3},
        {INF, INF, INF, 0, 2},
        {INF, INF, INF, INF, 0}
    };
    
    //Una matriz mas grande para probar
    /*
    vector<vector<int>> c = {
    {0, 5, 3, 1, 7, INF, INF, 9, 4, INF},
    {INF, 0, 8, 4, 2, 7, INF, 6, INF, 3},
    {INF, INF, 0, 2, 3, 9, INF, 8, INF, 1},
    {INF, INF, INF, 0, 2, 8, 5, 5, 6, 4},
    {INF, INF, INF, INF, 0, 6, 3, INF, 2, 5},
    {INF, INF, INF, INF, INF, 0, 4, 3, INF, 2},
    {INF, INF, INF, INF, INF, INF, 0, 7, 9, 3},
    {INF, INF, INF, INF, INF, INF, INF, 0, 2, 6},
    {INF, INF, INF, INF, INF, INF, INF, INF, 0, 5},
    {INF, INF, INF, INF, INF, INF, INF, INF, INF, 0}
    };
    */
    
    
    cout << "\n\n Matriz de costes iniciales: \n\n";
    printMatrix(c);

    vector<vector<int>> distMin;
    vector<vector<int>> predecesores;

    // Calcular los costos mínimos y la matriz de predecesores usando Floyd-Warshall
    floydWarshall(c, distMin, predecesores);

    // Imprimir la matriz de costos mínimos
    cout << "\n\n Matriz de distancias: \n\n";
    printMatrix(distMin);

    // Recuperar e imprimir el camino más corto entre dos nodos
    int i; // nodo de inicio
    int f; // nodo de llegada
    cout << " \n Indique el pueblo de inicio y el pueblo final de su trayecto en el intervalo [1,5]:\n";
    cin >> i >> f;
    while( i > f){
        cout<< "No puede ir a contracorriente, debe de introducir un valor inicial menor que el final, vuelva a introducir los datos [1,5]:\n";
        cin >> i >> f;
    }
    i--;
    f--;
    vector<int> path;

    //Recupera el trayecto más corto de los putnos introducidos
    getPath(i, f, predecesores, path);

    cout << "Camino más corto (con un coste de " << distMin[i][f] <<  ") de " << i+1 << " a " << f+1 << ":" << endl;
    //Imprime el camino más corto desde el punto inicial y final introducidos
    for (int i = 0 ; i < path.size() ; i++) {
        if (i != 0)
            cout << " -> ";
        cout << path[i]+1;
    }
    cout << endl;

    return 0;
}
