#include <stdio.h>
#include <stdlib.h>

typedef struct Graph{
    int V;
    int E;
    int **Adj;
}Graph;

int main(){
    int i,u,v;
    Graph *G = (Graph *)malloc(sizeof(Graph));
    printf("Enter the number of vertices and edges: ");
    scanf("%d%d",&G->V,&G->E);
    G->Adj = (int **)malloc(sizeof(int *)*G->V);
    for(i=0;i<G->V;i++){
        G->Adj[i] = (int *)malloc(sizeof(int)*G->V);
    }
    
    for(u=0;u<G->V;u++){
        for(v=0;v<G->V;v++){
            G->Adj[u][v] = 0;
        }
    }
    printf("Enter the end vertices of each edge and its value: ");
    for(i=0;i<G->E;i++){
        scanf("%d%d",&u,&v);
        G->Adj[u][v] = 1;
        G->Adj[v][u] = 1;
    }
    printf("The adjacency matrix is: \n");
    for(u=0;u<G->V;u++){
        for(v=0;v<G->V;v++){
            printf("%d ",G->Adj[u][v]);
        }
        printf("\n");
    }

    free(G);
    return 0;
}