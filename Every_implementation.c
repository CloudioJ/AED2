/*
Autores: 

Claudio Luis da Silva Machado Junior - 19200320
Marcelo Pereira Vargas Rodrigues - 19100322
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Edge {
    int src;
    int dest;
    int weight;
} Edge;

typedef struct Subset {
    int parent;
    int rank;
} Subset;

typedef struct Graph{
    int V;
    int E;
    int **Adj;
	int *dist;
    int *parent;
}Graph;

// Prototypes
void input(Graph *G, int* vertD);
void initialize(Graph *G);
void connect(Graph *G);
void printGraph(Graph *G);
void dijkstra(Graph *G, int *vertD);
void kruskal(Graph *G);
void prim(Graph *G, int src);
void freeGraph(Graph *G);
void Union(Subset subsets[], int x, int y);
int find(Subset subsets[], int i);
int minKey(Graph *G, int key[], int mstSet[]);


// Cute little menu
int main() {
    Graph *G = (Graph *)malloc(sizeof(Graph));
	int sel=0;
	
	printf(" _____________________________________________________\n");
	printf("|  Escolha o algoritimo que deseja usar:              |\n");
	printf("|                                                     |\n");
	printf("|  0 - Dijkistra                                      |\n");
	printf("|  1 - Kruskal                                        |\n");
	printf("|  2 - Prim                                           |\n");
	printf("|  9 - Sair                                           |\n");
	printf("|_____________________________________________________|\n");
	scanf("%d", &sel);

    int src = 0;
    int *vertD;
    vertD = (int *)malloc(sizeof(int) * 2);

    if (sel == 0){
        input(G, vertD);
    } else {
        input(G, NULL);
    }

    initialize(G);
    connect(G);
    printGraph(G);

	switch (sel)
	{
	case 0:
		dijkstra(G, vertD);
		break;
	case 1:
		kruskal(G);
		break;
	case 2:
		prim(G, src);
		break;
	default:
		break;
	}
    
    free(vertD);
	freeGraph(G);
	return 0;
}

// Get user input
void input(Graph *G, int *vertD){
	// int vert=0, edge=0;
    // do {
    // 	printf("\nO numero maximo de vertices e 20 e o minimo e 1");
    // 	printf("\nInsira o numero desejado de vertices: ");
    // 	scanf("%d", &vert);
    // 	printf("Insira o numero desejado de arestas: ");
    // 	scanf("%d", &edge);
    // }while (vert > 20 || vert < 1);
    // G->V = vert;
    // G->E = edge;
    G->V = 9;
    G->E = 14;
	
	if (vertD != NULL) {
		printf("Escolha o vertice de origem para o algoritmo de Dijkstra: ");
    	scanf("%d", &vertD[0]);
		printf("Escolha o vertice final para o algoritmo de Dijkstra: ");
    	scanf("%d", &vertD[1]);
		return;
	}
}

// Initialize the Graph
void initialize(Graph *G){
    G->Adj = (int **)malloc(sizeof(int *)*G->V);
	G->dist = (int *)malloc(sizeof(int) * G->V);
    G->parent = (int *)malloc(sizeof(int) * G->V);

    for(int i=0; i<G->V; i++)
        G->Adj[i] = (int *)malloc(sizeof(int)*G->V);

    for(int i=0; i<G->V; i++){
        for(int j=0; j<G->V; j++)
            G->Adj[i][j] = 0;
    }
}

// Connect the dots
void connect(Graph *G){
	// int vert1=0, vert2=0, value=0;
	// for(int i=0; i<G->E; i++){
	// 	do {
	// 		printf("\nDigite os vertices onde cada aresta e conectada:\n");
	// 		printf("Vertice inicial: ");
	// 		scanf("%d", &vert1);
	// 		printf("Vertice final: ");
	// 		scanf("%d", &vert2);
	// 	}while ((vert1 > 20 || vert1 < 0) || (vert2 > 20 || vert2 < 0));
	// 	printf("Valor da aresta: ");
	// 	scanf("%d", &value);

    //     G->Adj[vert1][vert2] = value;
    //     G->Adj[vert2][vert1] = value;
    // }

    // Hard coded graph
    G->V = 9;
    G->E = 14;

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
}

// Dijkstra it up
void dijkstra(Graph *G, int *vertD) {
    bool visited[G->V];
    for (int i=0; i<G->V; i++) {
        G->dist[i] = INT_MAX;
        G->parent[i] = -1;
        visited[i] = false;
    }

    G->dist[vertD[0]] = 0;

    for (int i=0; i<G->V - 1; i++) {
        int u = -1;
        for (int v=0; v<G->V; v++) {
            if (!visited[v] && (u == -1 || G->dist[v] < G->dist[u]))
                u = v;
        }

        visited[u] = true;

        for (int v=0; v<G->V; v++) {
            if (!visited[v] && G->Adj[u][v] && G->dist[u] != INT_MAX && G->dist[u] + G->Adj[u][v] < G->dist[v]) {
                G->dist[v] = G->dist[u] + G->Adj[u][v];
                G->parent[v] = u;
            }
        }
    }
	
	printf("\nDistancia entre o vertice %d e o vertice %d: %d\n", vertD[0], vertD[1], G->dist[vertD[1]]);
}

// Kruskal it up
void kruskal(Graph *G) {
    int V = G->V;
    Edge *edges = (Edge *)malloc(sizeof(Edge) * G->E);
    int edgeCount = 0;

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

    for (int i = 0; i < G->E - 1; i++) {
        for (int j = 0; j < G->E - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    Subset *subsets = (Subset *)malloc(sizeof(Subset) * V);
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    Edge *mst = (Edge *)malloc(sizeof(Edge) * (V - 1));
    int mstCount = 0;
    int i = 0;

    while (mstCount < V - 1 && i < G->E) {
        Edge nextEdge = edges[i++];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        if (x != y) {
            mst[mstCount++] = nextEdge;
            Union(subsets, x, y);
        }
    }

    printf("\nMenor caminho por peso da aresta:\n");
    for (int i = 0; i < mstCount; i++)
        printf("(%d,%d)%d    ", mst[i].src, mst[i].dest, mst[i].weight);

    free(edges);
    free(subsets);
    free(mst);
}

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Prim it up
void prim(Graph *G, int src){
    int parent[G->V];
    int key[G->V];
    int mstSet[G->V];

    for (int i=0; i<G->V; i++){
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[src] = 0;
    parent[src] = -1;

    for (int count=0; count<G->V-1; count++){
        int u = minKey(G, key, mstSet);
        mstSet[u] = 1;

        for (int v=0; v<G->V; v++){
            if (G->Adj[u][v] && mstSet[v] == 0 && G->Adj[u][v] < key[v]){
                parent[v] = u;
                key[v] = G->Adj[u][v];
            }
        }
    }

    printf("\nMenor caminho por peso da aresta:\n");
    for (int i = 0; i < G->V; i++){
        if(i != src){
            printf("(%d,%d)%d    ", parent[i], i, G->Adj[i][parent[i]]);
        }
    }
}

int minKey(Graph *G, int key[], int mstSet[]){
    int min = INT_MAX;
    int min_index = 0;

    for (int v=0; v<G->V; v++){
        if (mstSet[v] == 0 && key[v] < min){
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

// Print the adjacency matrix
void printGraph(Graph *G){
	printf("Matriz de adjacencia:\n");
	for(int i=0; i<G->V; i++){
		for(int j=0; j<G->V; j++)
			printf("%d\t",G->Adj[i][j]);
		printf("\n");
	}
}

// Free the graph
void freeGraph(Graph *G){
    for(int i=0; i<G->V; i++)
        free(G->Adj[i]);
    free(G->Adj);
    free(G->dist);
    free(G->parent);
    free(G);
}