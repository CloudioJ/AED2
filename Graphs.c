/*
Autores: 

Claudio Luis da Silva Machado Junior - 19200320
Marcelo Pereira Vargas Rodrigues - 19100322
*/

#include <stdio.h>
#include <stdlib.h>

// Cria a estrutura do grafo
typedef struct Graph{
    int V;
    int A;
    int **Adj;
} Graph;

Graph *addArestas(Graph *G, int v1, int v2, int value, int size);
Graph initGraph(Graph *G);
void freeGraph(Graph *G);
void printGraph(Graph *G);
int findMinKey(int key[], int mstSet[], int V);
void primMST(Graph *G, int source);

int main(){
    // Inicializa os valores do grafo
    int v1 = 0, v2 = 0, value = 0;
    Graph *G = (Graph *)malloc(sizeof(Graph));

    // Recebe o numero de vertices e arestas
    printf("Escreva o numero de vertices e arestas: ");
    scanf("%d%d",&G->V, &G->A);
    G->Adj = (int **)malloc(sizeof(int *)*G->V);

    // Inicializa o grafo
    initGraph(G);
    // Adiciona as arestas
    addArestas(G, v1, v2, value, G->A);
    // Printa a matriz de adjacencia
    printGraph(G);

    // Libera o grafo
    freeGraph(G);
    return 0;
}

Graph *addArestas(Graph *G, int v1, int v2, int value, int size){
    // Recebe os valores das arestas
    for(int i = 0; i < size; i++){
        do{
            printf("Escolha os vertices onde sera implementada a aresta e o seu respectivo valor: ");
            scanf("%d%d%d", &v1, &v2, &value);
        } while(v1 >= G->V || v2 >= G->V || v1 < 0 || v2 < 0);

        G->Adj[v1][v2] = value;
        G->Adj[v2][v1] = value;
    }

    return G;
}

Graph initGraph(Graph *G){
    // Inicializa a matriz de adjacencia
    G->Adj = (int **)malloc(sizeof(int *)*G->V);
    for(int i = 0; i < G->V; i++){
        G->Adj[i] = (int *)malloc(sizeof(int)*G->V);
    }
    for(int u = 0; u < G->V; u++){
        for(int v = 0; v < G->V; v++){
            G->Adj[u][v] = 0;
        }
    }
    return *G;
}

void printGraph(Graph *G){
    // Printa a matriz de adjacencia
    printf("Matriz de adjacencia: \n");
    for(int i = 0; i < G->V; i++){
        for(int j = 0; j < G->V; j++){
            printf("%d ", G->Adj[i][j]);
        }
        printf("\n");
    }
}

void freeGraph(Graph *G){
    // Libera a memoria alocada para o grafo
    for(int i = 0; i < G->V; i++){
        free(G->Adj[i]);
    }
    free(G->Adj);
    free(G);
}