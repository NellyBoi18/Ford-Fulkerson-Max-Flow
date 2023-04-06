#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 1000

int graph[MAX_NODES][MAX_NODES]; // Adjacency matrix
int flow[MAX_NODES][MAX_NODES]; // Flow on each edge
int residual[MAX_NODES][MAX_NODES]; // Residual capacity on each edge
int parent[MAX_NODES]; // Parent of each node in the augmenting path
int visited[MAX_NODES]; // Mark visited nodes
int queue[MAX_NODES]; // Queue for BFS

int min(int a, int b) {
    return a < b ? a : b;
}

int bfs(int source, int sink, int numNodes) {
    // Initialize visited and parent arrays
    for (int i = 0; i < numNodes; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }
    visited[source] = 1;

    // Initialize queue with source node
    int front = 0, rear = 0;
    queue[rear++] = source;

    while (front < rear) {
        int node = queue[front++];

        // Visit each neighbor of node
        for (int neighbor = 0; neighbor < numNodes; neighbor++) {
            // If neighbor is not visited and has residual capacity
            if (!visited[neighbor] && residual[node][neighbor] > 0) {
                // Mark neighbor as visited and set its parent to node
                visited[neighbor] = 1;
                parent[neighbor] = node;
                // Add neighbor to queue
                queue[rear++] = neighbor;

                // If neighbor is sink node, return residual capacity
                if (neighbor == sink) {
                    return residual[node][neighbor];
                }
            }
        }
    }

    // No augmenting path was found
    return 0;
}

int fordFulkerson(int source, int sink, int numNodes) {
    int maxFlow = 0;

    // Initialize flow and residual graph
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            flow[i][j] = 0;
            residual[i][j] = graph[i][j];
        }
    }

    // Repeat until no augmenting path can be found
    while (1) {
        int augmentingFlow = bfs(source, sink, numNodes);

        if (augmentingFlow == 0) {
            break;
        }

        // Update flow and residual graph along augmenting path
        int node = sink;

        while (node != source) {
            int prev = parent[node];
            flow[prev][node] += augmentingFlow;
            flow[node][prev] -= augmentingFlow;
            residual[prev][node] -= augmentingFlow;
            residual[node][prev] += augmentingFlow;
            node = prev;
        }

        maxFlow += augmentingFlow;
    }

    return maxFlow;
}

int main() {
    int numInstances;
    scanf("%d", &numInstances);
    // Array to store the maximum flow for each instance
    int *maxFlow = malloc(numInstances * sizeof(int));

    for (int i = 0; i < numInstances; i++) {
        int numNodes, numEdges;
        scanf("%d %d", &numNodes, &numEdges);

        // Initialize adjacency matrix
        for (int j = 0; j < numEdges; j++) {
            int sourceNode, destNode, capacity;
            scanf("%d %d %d", &sourceNode, &destNode, &capacity);
            graph[sourceNode-1][destNode-1] = capacity;
        }

        // int maxFlow = fordFulkerson(0, numNodes-1, numNodes);
        // printf("%d\n", maxFlow);
        maxFlow[i] = fordFulkerson(0, numNodes-1, numNodes);

        // Reset graph for next instance
        for (int j = 0; j < numNodes; j++) {
            for (int k = 0; k < numNodes; k++) {
                graph[j][k] = 0;
            }
        }
    }

    // Print out the maximum value for each instance
    for (int i = 0; i < numInstances; i++) {
        printf("%d\n", maxFlow[i]);
    }

    free(maxFlow);

    return 0;
}