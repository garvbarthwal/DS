//FINAL

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Node structure for adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Graph structure using adjacency list
typedef struct Graph {
    int vertices;           // Number of vertices
    Node* adjList[MAX];     // Array of adjacency lists
    int status[MAX];        // Status array to track visited nodes
} Graph;

// Function prototypes
void initializeGraph(Graph* graph, int vertices);
void addEdge(Graph* graph, int u, int v);
void DFS(Graph* graph, int start);
void BFS(Graph* graph, int start);
Node* createNode(int vertex);
void loadGraphFromFile(Graph* graph, const char* filename);
void printAdjacencyList(Graph* graph);

// Function to initialize the graph
void initializeGraph(Graph* graph, int vertices) {
    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;  // Initialize adjacency list to NULL
        graph->status[i] = 0;      // Mark all vertices as unvisited
    }
}

// Function to create a new node for the adjacency list
Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int u, int v) {
    // Add edge from u to v
    Node* newNode = createNode(v);
    newNode->next = graph->adjList[u];
    graph->adjList[u] = newNode;

    // Add edge from v to u (for undirected graph)
    newNode = createNode(u);
    newNode->next = graph->adjList[v];
    graph->adjList[v] = newNode;
}

// Function to print the adjacency list
void printAdjacencyList(Graph* graph) {
    printf("Adjacency List:\n");
    for (int i = 0; i < graph->vertices; i++) {
        printf("Node %d is connected to", i + 1); // Print the node number (1-based index)

        Node* temp = graph->adjList[i];
        if (temp == NULL) {
            printf(" No adjacent vertices.\n"); // Handle nodes with no edges
        } else {
            while (temp) {
                printf(" %d", temp->vertex + 1); // Print the adjacent vertex (1-based index)
                temp = temp->next;
            }
            printf("\n");
        }
    }
}


// Function to load graph from a file
void loadGraphFromFile(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return;
    }

    int vertices, edges;
    fscanf(file, "%d %d", &vertices, &edges);
    initializeGraph(graph, vertices);

    for (int i = 0; i < edges; i++) {
        int u, v;
        fscanf(file, "%d %d", &u, &v);
        addEdge(graph, u - 1, v - 1); // Adjusting to 0-based index
    }

    fclose(file);
    printf("Graph loaded successfully from %s\n", filename);
}

// Function to perform DFS traversal
void DFS(Graph* graph, int start) {
    if (start < 0 || start >= graph->vertices) {
        printf("Invalid starting vertex.\n");
        return;
    }

    // Initialize visited array to avoid resetting global status array
    int visited[MAX] = {0};

    printf("DFS Traversal (using stack):\n");

    int stack[MAX], top = -1;
    stack[++top] = start;

    while (top >= 0) {
        int current = stack[top--];

        // Skip if already visited
        if (visited[current] == 1) {
            continue;
        }

        visited[current] = 1;
        printf("%d ", current + 1); // Convert back to 1-based index

        // Push all unvisited neighbors to the stack
        Node* temp = graph->adjList[current];
        while (temp) {
            if (!visited[temp->vertex]) {
                stack[++top] = temp->vertex;
            }
            temp = temp->next;
        }
    }

    printf("\n");
}

// Function to perform BFS traversal
void BFS(Graph* graph, int start) {
    if (start < 0 || start >= graph->vertices) {
        printf("Invalid starting vertex.\n");
        return;
    }

    printf("BFS Traversal (using queue):\n");

    int queue[MAX], front = 0, rear = 0;
    int visited[MAX] = {0};  // Use local visited array for BFS
    queue[rear++] = start;
    visited[start] = 1;

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current + 1); // Convert back to 1-based index

        Node* temp = graph->adjList[current];
        while (temp) {
            if (!visited[temp->vertex]) {
                queue[rear++] = temp->vertex;
                visited[temp->vertex] = 1;
            }
            temp = temp->next;
        }
    }

    printf("\n");
}

int main() {
    int choice, vertices, edges, u, v, start;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    Graph graph;
    // Initialize graph
    initializeGraph(&graph, vertices); // Flag to track if the graph is initialized

    do {
        printf("\nMenu:\n");
        printf("1. Add edge\n");
        printf("2. Perform DFS traversal\n");
        printf("3. Perform BFS traversal\n");
        printf("4. Load graph from file\n");
        printf("5. Print adjacency list\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Add more edges
                printf("Enter the number of edges to add: ");
                scanf("%d", &edges);

                printf("Enter the edges (u, v):\n");
                for (int i = 0; i < edges; i++) {
                    printf("Edge %d:\n", i + 1);
                    printf("  Enter source vertex (u): ");
                    scanf("%d", &u);
                    printf("  Enter destination vertex (v): ");
                    scanf("%d", &v);
                    addEdge(&graph, u - 1, v - 1); // Adjusting to 0-based index
                }
                break;

            case 2:
                printf("Enter the starting vertex for DFS traversal: ");
                scanf("%d", &start);
                DFS(&graph, start - 1); // Adjusting to 0-based index
                break;

            case 3:
                printf("Enter the starting vertex for BFS traversal: ");
                scanf("%d", &start);
                BFS(&graph, start - 1); // Adjusting to 0-based index
                break;

            case 4:
                {
                    char filename[100];
                    printf("Enter the filename to load the graph from: ");
                    scanf("%s", filename);
                    loadGraphFromFile(&graph, filename);
                }
                break;

            case 5:
                printAdjacencyList(&graph);
                break;

            case 6:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
