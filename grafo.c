#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define INF INT_MAX
#define V 5

int minDistance(int dist[], bool visitado[]) {
    int min = INF, min_index;

    for (int v = 0; v < V; v++) {
        if (!visitado[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}


void imprimirCaminho(int parent[], int j) {
    if (parent[j] == -1) {
        return;
    }
    imprimirCaminho(parent, parent[j]);
    printf(" -> %c", 'A' + j);
}


void imprimirSolucao(int dist[], int parent[]) {
    printf("Cidade\tDistância\tCaminho\n");
    for (int i = 0; i < V; i++) {
        printf("%c -> %c\t", 'A', 'A' + i);
        if (dist[i] == INF) {
            printf("INF\t\tNenhum caminho disponível\n");
        } else {
            printf("%d\t\t%c", dist[i], 'A');
            imprimirCaminho(parent, i);
            printf("\n");
        }
    }
}

void dijkstra(int grafo[V][V], int src) {
    int dist[V];       // Array para armazenar a menor distância de cada vértice
    bool visitado[V];  // Array com os vértices já visitados
    int parent[V];     // Array para armazenar o caminho mais curto

    // Inicializa as distâncias e visitados
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visitado[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0; // A distância da origem para ela mesma é 0

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visitado); // Encontra o vértice com a menor distância
        visitado[u] = true;

        // Atualiza as distâncias dos vizinhos de u
        for (int v = 0; v < V; v++) {
            if (!visitado[v] && grafo[u][v] && dist[u] != INF &&
                dist[u] + grafo[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + grafo[u][v];
            }
        }
    }

    imprimirSolucao(dist, parent);
}

int main() {
    // Matriz representando o grafo
    int grafo[V][V] = {
        {0, 4, 2, 7, 0}, // A : B, C, D
        {4, 0, 1, 0, 1}, // B : A, C, E
        {2, 1, 0, 3, 3}, // C : A, B, D, E
        {7, 0, 3, 0, 2}, // D : A, C, E
        {0, 1, 3, 2, 0}  // E : B, C, D
    };

    printf("menor caminho usando o algoritmo de Dijkstra:\n\n");
    dijkstra(grafo, 0); // nó A (índice 0)

    return 0;
}
