#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
void prim(Graph *G, int src);

int main(){
    // Inicializa os valores do grafo
    // int v1 = 0, v2 = 0, value = 0;
    Graph *G = (Graph *)malloc(sizeof(Graph));

    // Recebe o numero de vertices e arestas
    printf("Escreva o numero de vertices e arestas: ");
    // scanf("%d%d",&G->V, &G->A);
    G->V = 9;
    G->A = 14;
    G->Adj = (int **)malloc(sizeof(int *)*G->V);

    // Inicializa o grafo
    initGraph(G);
    // Adiciona as arestas
    // addArestas(G, v1, v2, value, G->A);
    G->Adj[0][1] = 4;
    G->Adj[0][7] = 8;
    G->Adj[1][2] = 8;
    G->Adj[1][7] = 11;
    G->Adj[2][3] = 7;
    G->Adj[2][8] = 2;
    G->Adj[2][5] = 4;
    G->Adj[3][4] = 9;
    G->Adj[3][5] = 14;
    G->Adj[4][5] = 10;
    G->Adj[5][6] = 2;
    G->Adj[6][7] = 1;
    G->Adj[6][8] = 6;
    G->Adj[7][8] = 7;
    G->Adj[1][0] = 4;
    G->Adj[7][0] = 8;
    G->Adj[2][1] = 8;
    G->Adj[7][1] = 11;
    G->Adj[3][2] = 7;
    G->Adj[8][2] = 2;
    G->Adj[5][2] = 4;
    G->Adj[4][3] = 9;
    G->Adj[5][3] = 14;
    G->Adj[5][4] = 10;
    G->Adj[6][5] = 2;
    G->Adj[7][6] = 1;
    G->Adj[8][6] = 6;
    G->Adj[8][7] = 7;
    
    // Printa a matriz de adjacencia
    printGraph(G);

    // Recebe o vertice de origem
    int src;
    do {
        printf("Escolha um vertice de origem (0 to %d): ", G->V - 1);
        scanf("%d", &src);
    } while (src < 0 || src >= G->V);

    // Executa o algoritmo de Prim
    prim(G, src);

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
            printf("\t%d", G->Adj[i][j]);
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

int findMinKey(int key[], int mstSet[], int V){
    // Inicializa o valor minimo
    int min = INT_MAX, min_index;
    for(int v = 0; v < V; v++){
        if(mstSet[v] == 0 && key[v] < min){
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void prim(Graph *G, int src){
    // Inicializa os vetores
    int parent[G->V];
    int key[G->V];
    int mstSet[G->V]; 

    // Inicializa todas as keys como infinito e mstSet como falso
    for(int i = 0; i < G->V; i++){
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    // Começa com o vertice selecionado como root da MST
    key[src] = 0; 
    parent[src] = -1; 

    // O algoritmo roda V vezes
    for(int count = 0; count < G->V - 1; count++){
        int u = findMinKey(key, mstSet, G->V); // Escolhe o valor de key minimo do vertice que não está na MST
        mstSet[u] = 1; // Adiciona o vertice escolhido na MST

        // Muda o valor da key e parent dos vertices adjacentes do vertice escolhido
        for(int v = 0; v < G->V; v++){
            if(G->Adj[u][v] && mstSet[v] == 0 && G->Adj[u][v] < key[v]){
                parent[v] = u;
                key[v] = G->Adj[u][v];
            }
        }
    }

    // Printa a MST
    printf("\nMinimum Spanning Tree (MST) usando Prim com a origem em %d:\n", src);
    for(int i = 0; i < G->V; i++){
        if (i != src) {
            printf("%d - %d: %d\n", parent[i], i, G->Adj[i][parent[i]]);
        }
    }
}