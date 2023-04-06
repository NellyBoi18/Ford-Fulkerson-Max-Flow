#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 1000

int graph[MAX_NODES][MAX_NODES]; // adjacency matrix
int flow[MAX_NODES][MAX_NODES]; // flow on each edge
int residual[MAX_NODES][MAX_NODES]; // residual capacity on each edge
int parent[MAX_NODES]; // parent of each node in the augmenting path
int visited[MAX_NODES]; // flag to mark visited nodes
int queue[MAX_NODES]; // queue for BFS

int min(int a, int b) {
    return a < b ? a : b;
}

int bfs(int source, int sink, int numNodes) {
    // initialize visited and parent arrays
    for (int i = 0; i < numNodes; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }

    visited[source] = 1;

    // initialize queue with source node
    int front = 0, rear = 0;
    queue[rear++] = source;

    while (front < rear) {
        int node = queue[front++];

        // visit each neighbor of node
        for (int neighbor = 0; neighbor < numNodes; neighbor++) {
            // if neighbor is not visited and has residual capacity
            if (!visited[neighbor] && residual[node][neighbor] > 0) {
                // mark neighbor as visited and set its parent to node
                visited[neighbor] = 1;
                parent[neighbor] = node;
                // add neighbor to queue
                queue[rear++] = neighbor;

                // if neighbor is sink node, return residual capacity
                if (neighbor == sink) {
                    return residual[node][neighbor];
                }
            }
        }
    }
    // no augmenting path was found
    return 0;
}

int ford_fulkerson(int source, int sink, int numNodes) {
    int max_flow = 0;

    // initialize flow and residual graph
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            flow[i][j] = 0;
            residual[i][j] = graph[i][j];
        }
    }

    // repeat until no augmenting path can be found
    while (1) {
        int augmenting_flow = bfs(source, sink, numNodes);

        if (augmenting_flow == 0) {
            break;
        }

        // update flow and residual graph along augmenting path
        int node = sink;

        while (node != source) {
            int prev = parent[node];
            flow[prev][node] += augmenting_flow;
            flow[node][prev] -= augmenting_flow;
            residual[prev][node] -= augmenting_flow;
            residual[node][prev] += augmenting_flow;
            node = prev;
        }

        max_flow += augmenting_flow;
    }

    return max_flow;
}

int main() {
    int numInstances;
    scanf("%d", &numInstances);

    for (int i = 0; i < numInstances; i++) {
        int numNodes, m;
        scanf("%d %d", &numNodes, &m);

        // initialize adjacency matrix
        for (int j = 0; j < m; j++) {
            int u, v, capacity;
            scanf("%d %d %d", &u, &v, &capacity);
            graph[u-1][v-1] = capacity;
        }

        int max_flow = ford_fulkerson(0, numNodes-1, numNodes);
        printf("%d\n", max_flow);

        // reset graph for next instance
        for (int j = 0; j < numNodes; j++) {
            for (int k = 0; k < numNodes; k++) {
                graph[j][k] = 0;
            }
        }
    }

    return 0;
}