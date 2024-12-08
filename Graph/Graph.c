#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define INF 99999 // Define a large value to represent infinity

// Dijkstra's Algorithm Structures
typedef struct Graph {
    int vertices;
    int adjmatrix[MAX][MAX];
} Graph;

// Kruskal's Algorithm Structures
typedef struct mst {
    int weight, u, v;
} Edges;

typedef struct disjoint {
    int *parent, *rank;
    int size;
} disjoint;

// Function Prototypes for Dijkstra's
void initializeGraph(Graph*, int);
void addEdgesDijkstra(Graph*, int, int, int);
void dijkstra(Graph*, int);
void printPath(int*, int, int);

// Function Prototypes for Kruskal's
disjoint* createdisjoint(int);
int find(disjoint*, int);
disjoint* unionsets(disjoint*, int, int);
int compare(const void*, const void*);
void kruskal(Edges*, int, int);

// Dijkstra's Algorithm Functions
void initializeGraph(Graph* graph, int vertices) {
    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i == j) {
                graph->adjmatrix[i][j] = 0;
            } else {
                graph->adjmatrix[i][j] = INF;
            }
        }
    }
}

void addEdgesDijkstra(Graph* graph, int u, int v, int weight) {
    graph->adjmatrix[u][v] = weight;
    graph->adjmatrix[v][u] = weight; // For undirected graph
}

void dijkstra(Graph* graph, int start) {
    int distance[MAX], visited[MAX], previous[MAX];
    for (int i = 0; i < graph->vertices; i++) {
        distance[i] = INF;
        visited[i] = 0;
        previous[i] = -1; // No previous node initially
    }
    distance[start] = 0;

    for (int i = 0; i < graph->vertices - 1; i++) {
        int minDist = INF, u = -1;
        for (int v = 0; v < graph->vertices; v++) {
            if (!visited[v] && distance[v] < minDist) {
                minDist = distance[v];
                u = v;
            }
        }

        visited[u] = 1;

        for (int v = 0; v < graph->vertices; v++) {
            if (!visited[v] && graph->adjmatrix[u][v] != INF &&
                distance[u] + graph->adjmatrix[u][v] < distance[v]) {
                distance[v] = distance[u] + graph->adjmatrix[u][v];
                previous[v] = u; // Update previous vertex
            }
        }
    }

    // Print distances and paths
    for (int i = 0; i < graph->vertices; i++) {
        if (i != start) {
            printf("The distance from %d to %d = %d. ", start, i, distance[i]);
            printf("Path: ");
            printPath(previous, start, i);
            printf("\n");
        }
    }
}

void printPath(int* previous, int start, int vertex) {
    if (vertex == start) {
        printf("%d", start);
        return;
    }
    if (previous[vertex] == -1) {
        printf("No path");
        return;
    }
    printPath(previous, start, previous[vertex]);
    printf(" -> %d", vertex);
}

// Kruskal's Algorithm Functions
disjoint* createdisjoint(int size) {
    disjoint* ds = (disjoint*)malloc(sizeof(disjoint));
    ds->parent = (int*)malloc(sizeof(int) * size);
    ds->rank = (int*)malloc(sizeof(int) * size);
    ds->size = size;
    for (int i = 0; i < size; i++) {
        ds->parent[i] = i;
        ds->rank[i] = 0;
    }
    return ds;
}

int find(disjoint* ds, int x) {
    if (ds->parent[x] != x)
        ds->parent[x] = find(ds, ds->parent[x]);
    return ds->parent[x];
}

disjoint* unionsets(disjoint* ds, int x, int y) {
    int rootX = find(ds, x);
    int rootY = find(ds, y);
    if (rootX != rootY) {
        if (ds->rank[rootX] < ds->rank[rootY])
            ds->parent[rootX] = rootY;
        else if (ds->rank[rootY] < ds->rank[rootX])
            ds->parent[rootY] = rootX;
        else {
            ds->parent[rootY] = rootX;
            ds->rank[rootX]++;
        }
    }
    return ds;
}

int compare(const void* a, const void* b) {
    return ((Edges*)a)->weight - ((Edges*)b)->weight;
}

void kruskal(Edges* edges, int numEdges, int numvertices) {
    qsort(edges, numEdges, sizeof(Edges), compare);
    disjoint* ds = createdisjoint(numvertices);
    printf("Minimum Spanning Tree:\n");
    int mstweight = 0;
    for (int i = 0; i < numEdges; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;
        if (find(ds, u) != find(ds, v)) {
            printf("%d--%d=%d\n", u, v, weight);
            mstweight += weight;
            unionsets(ds, u, v);
        }
    }
    printf("Total weight of MST: %d\n", mstweight);
    free(ds->parent);
    free(ds->rank);
    free(ds);
}

int main() {
    int choice, numEdges, numvertices, u, v, weight, start;
    Graph graph;
    Edges* edges = NULL;

    do {
        printf("\nMENU\n");
        printf("1: Add edges (Dijkstra)\n");
        printf("2: Run Dijkstra's Algorithm\n");
        printf("3: Add edges (Kruskal)\n");
        printf("4: Run Kruskal's Algorithm\n");
        printf("5: Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of vertices: ");
                scanf("%d", &numvertices);
                initializeGraph(&graph, numvertices);
                printf("Enter the number of edges: ");
                scanf("%d", &numEdges);
                for (int i = 0; i < numEdges; i++) {
                    printf("Enter edge %d (u v weight): ", i + 1);
                    scanf("%d %d %d", &u, &v, &weight);
                    addEdgesDijkstra(&graph, u, v, weight);
                }
                break;

            case 2:
                printf("Enter the starting vertex for Dijkstra: ");
                scanf("%d", &start);
                dijkstra(&graph, start);
                break;

            case 3:
                printf("Enter the number of vertices for Kruskal: ");
                scanf("%d", &numvertices);
                printf("Enter the number of edges: ");
                scanf("%d", &numEdges);
                edges = (Edges*)malloc(sizeof(Edges) * numEdges);
                printf("Enter the edges (u v weight):\n");
                for (int i = 0; i < numEdges; i++) {
                    scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
                }
                break;

            case 4:
                if (edges != NULL) {
                    kruskal(edges, numEdges, numvertices);
                    free(edges);  // Free memory after usage
                } else {
                    printf("No edges added for Kruskal's algorithm.\n");
                }
                break;

            case 5:
                printf("Exiting program.\n");
                exit(0);
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (1);

    return 0;
}
