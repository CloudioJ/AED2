/*
Autores: 

Claudio Luis da Silva Machado Junior - 19200320
Marcelo Pereira Vargas Rodrigues - 19100322
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Cria a estrutura do grafo
typedef struct Graph {
    int V;
    int A;
    int **Adj;
    int *dist;
    int *parent;
} Graph;

Graph *addArestas(Graph *G, int v1, int v2, int value, int size);
Graph initGraph(Graph *G);
void dijkstra(Graph *G, int src);
void freeGraph(Graph *G);
void printGraph(Graph *G);

int main() {
    // Inicializa os valores do grafo
    int v1 = 0, v2 = 0, value = 0;
    Graph *G = (Graph *)malloc(sizeof(Graph));

    // Recebe o numero de vertices e arestas
    printf("Escreva o numero de vertices e arestas: ");
    scanf("%d %d", &G->V, &G->A);

    // Aloca memoria para o grafo
    G->Adj = (int **)malloc(sizeof(int *) * G->V);
    G->dist = (int *)malloc(sizeof(int) * G->V);
    G->parent = (int *)malloc(sizeof(int) * G->V);
    
    // Inicializa o grafo
    initGraph(G);
    // Adiciona as arestas
    addArestas(G, v1, v2, value, G->A);

    // Recebe o vertice de origem
    int src;
    printf("Escolha o vertice de origem para o algoritmo de Dijkstra: ");
    scanf("%d", &src);

    // Executa o algoritmo de Dijkstra
    dijkstra(G, src);
    // Printa a matriz de adjacencia e o vetor de distancias
    printGraph(G);

    // Libera o grafo
    freeGraph(G);
    return 0;
}

Graph *addArestas(Graph *G, int v1, int v2, int value, int size) {
    // Recebe os valores das arestas
    for (int i = 0; i < size; i++) {
        do {
            printf("Escolha os vertices onde sera implementada a aresta e o seu respectivo valor: ");
            scanf("%d %d %d", &v1, &v2, &value);
        } while (v1 >= G->V || v2 >= G->V || v1 < 0 || v2 < 0);

        G->Adj[v1][v2] = value;
        G->Adj[v2][v1] = value;
    }

    return G;
}

Graph initGraph(Graph *G) {
    // Inicializa a matriz de adjacencia
    G->Adj = (int **)malloc(sizeof(int *) * G->V);
    for (int i = 0; i < G->V; i++) {
        G->Adj[i] = (int *)malloc(sizeof(int) * G->V);
    }
    for (int u = 0; u < G->V; u++) {
        for (int v = 0; v < G->V; v++) {
            G->Adj[u][v] = 0;
        }
    }
    return *G;
}

void dijkstra(Graph *G, int src) {
    // Inicializa os vetores de distancias e pais e os booleanos de visitados
    bool visited[G->V];
    for (int i = 0; i < G->V; i++) {
        G->dist[i] = INT_MAX;
        G->parent[i] = -1;
        visited[i] = false;
    }

    // Inicializa a distancia da origem como 0
    G->dist[src] = 0;

    // Executa o algoritmo de Dijkstra
    for (int count = 0; count < G->V - 1; count++) {
        // Escolhe o vertice com a menor distancia
        int u = -1;
        for (int v = 0; v < G->V; v++) {
            if (!visited[v] && (u == -1 || G->dist[v] < G->dist[u])) {
                u = v;
            }
        }
        // Marca o vertice como visitado
        visited[u] = true;
        // Atualiza as distancias dos vertices adjacentes
        for (int v = 0; v < G->V; v++) {
            if (!visited[v] && G->Adj[u][v] && G->dist[u] != INT_MAX && G->dist[u] + G->Adj[u][v] < G->dist[v]) {
                G->dist[v] = G->dist[u] + G->Adj[u][v];
                G->parent[v] = u;
            }
        }
    }
}

void printGraph(Graph *G) {
    // Printa a matriz de adjacencia
    printf("Matriz de adjacencia: \n");
    for (int i = 0; i < G->V; i++) {
        for (int j = 0; j < G->V; j++) {
            printf("%d ", G->Adj[i][j]);
        }
        printf("\n");
    }

    // Printa o vetor de distancias
    printf("\n\nMenores distâncias a partir da origem: \n");
    for (int i = 0; i < G->V; i++) {
        printf("Vertice %d: %d\n", i, G->dist[i]);
    }
}

void freeGraph(Graph *G) {
    // Libera a memoria alocada para o grafo
    for (int i = 0; i < G->V; i++) {
        free(G->Adj[i]);
    }
    free(G->Adj);
    free(G->dist);
    free(G->parent);
    free(G);
}