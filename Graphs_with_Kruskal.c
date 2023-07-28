/*
Autores: 

Claudio Luis da Silva Machado Junior - 19200320
Marcelo Pereira Vargas Rodrigues - 19100322
*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura de uma aresta
typedef struct Edge {
    int src;
    int dest;
    int weight;
} Edge;

// Estrutura de um grafo
typedef struct Graph {
    int V;
    int A;
    int **Adj;
} Graph;

// Estrutura de um subconjunto
typedef struct Subset {
    int parent;
    int rank;
} Subset;

Graph *addArestas(Graph *G, int v1, int v2, int value, int size);
Graph initGraph(Graph *G);
void freeGraph(Graph *G);
void printGraph(Graph *G);
void kruskal(Graph *G);

// Funcoes para o algoritmo de Kruskal
int find(Subset subsets[], int i);
void Union(Subset subsets[], int x, int y);

int main() {
    // Inicializa os valores do grafo
    int v1 = 0, v2 = 0, value = 0;
    Graph *G = (Graph *)malloc(sizeof(Graph));

    // Recebe o numero de vertices e arestas
    printf("Escreva o numero de vertices e arestas: ");
    scanf("%d%d", &G->V, &G->A);
    G->Adj = (int **)malloc(sizeof(int *) * G->V);

    // Inicializa o grafo
    initGraph(G);
    // Adiciona as arestas
    addArestas(G, v1, v2, value, G->A);
    // Printa a matriz de adjacencia
    printGraph(G);

    // Executa o algoritmo de Kruskal
    kruskal(G);

    // Libera o grafo
    freeGraph(G);
    return 0;
}

Graph *addArestas(Graph *G, int v1, int v2, int value, int size) {
    // Recebe os valores das arestas
    for (int i = 0; i < size; i++) {
        do {
            printf("Escolha os vertices onde sera implementada a aresta e o seu respectivo valor: ");
            scanf("%d%d%d", &v1, &v2, &value);
        } while (v1 > G->V || v2 > G->V || v1 < 0 || v2 < 0);

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

void printGraph(Graph *G) {
    // Printa a matriz de adjacencia
    printf("Matriz de adjacencia: \n");
    for (int i = 0; i < G->V; i++) {
        for (int j = 0; j < G->V; j++) {
            printf("%d ", G->Adj[i][j]);
        }
        printf("\n");
    }
}

void freeGraph(Graph *G) {
    // Libera a memoria alocada para o grafo
    for (int i = 0; i < G->V; i++) {
        free(G->Adj[i]);
    }
    free(G->Adj);
    free(G);
}

void kruskal(Graph *G) {
    int V = G->V;
    Edge *edges = (Edge *)malloc(sizeof(Edge) * G->A);
    int edgeCount = 0;

    // Preenche o vetor de arestas
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (G->Adj[i][j] != 0) {
                edges[edgeCount].src = i;
                edges[edgeCount].dest = j;
                edges[edgeCount].weight = G->Adj[i][j];
                edgeCount++;
            }
        }
    }

    // Ordena as arestas
    for (int i = 0; i < G->A - 1; i++) {
        for (int j = 0; j < G->A - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    Subset *subsets = (Subset *)malloc(sizeof(Subset) * V);
    // Inicializa os subconjuntos
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    Edge *mst = (Edge *)malloc(sizeof(Edge) * (V - 1));
    int mstCount = 0;
    int i = 0;

    // Une os subconjuntos
    while (mstCount < V - 1 && i < G->A) {
        Edge nextEdge = edges[i++];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        if (x != y) {
            mst[mstCount++] = nextEdge;
            Union(subsets, x, y);
        }
    }
    // Printa a MST
    printf("\nMinimum Spanning Tree:\n");
    for (int i = 0; i < mstCount; i++) {
        printf("%d - %d : %d\n", mst[i].src, mst[i].dest, mst[i].weight);
    }

    // Libera a memoria alocada
    free(edges);
    free(subsets);
    free(mst);
}

int find(Subset subsets[], int i) {
    // Encontra o subconjunto de um vertice
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // Une dois subconjuntos
    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}