#include <stdio.h>
#include <stdlib.h>

typedef struct Graph{
    int V;
    int A;
    int **Adj;
} Graph;

Graph *addArestas(Graph *G, int v1, int v2, int value, int size);
Graph initGraph(Graph *G);
void freeGraph(Graph *G);
void printGraph(Graph *G);

int main(){
    int v1 = 0, v2 = 0, value = 0;
    Graph *G = (Graph *)malloc(sizeof(Graph));
    printf("Escreva o numero de vertices e arestas: "); scanf("%d%d",&G->V, &G->A);
    G->Adj = (int **)malloc(sizeof(int *)*G->V);

    initGraph(G);
    addArestas(G, v1, v2, value, G->A);
    printGraph(G);
    freeGraph(G);
    return 0;
}

Graph *addArestas(Graph *G, int v1, int v2, int value, int size){
    for(int i = 0; i < size; i++){
        do{
            printf("Escolha os vertices onde sera implementada a aresta e o seu respectivo valor: "); scanf("%d%d%d", &v1, &v2, &value);
        } while(v1 > G->V || v2 > G->V || v1 < 0 || v2 < 0);

        G->Adj[v1][v2] = value;
        G->Adj[v2][v1] = value;
    }

    return G;
}

Graph initGraph(Graph *G){
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
    printf("Matriz de adjacencia: \n");
    for(int i = 0; i < G->V; i++){
        for(int j = 0; j < G->V; j++){
            printf("%d ", G->Adj[i][j]);
        }
        printf("\n");
    }
}

void freeGraph(Graph *G){
    for(int i = 0; i < G->V; i++){
        free(G->Adj[i]);
    }
    free(G->Adj);
    free(G);
}