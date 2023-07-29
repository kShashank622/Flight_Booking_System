#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#define MAX_CITIES 5  // Replace with the number of cities you have

// Function to find the minimum distance vertex
int minDistance(int dist[], bool visited[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the path from source to destination
void printPath(int parent[], int dest) {
    if (parent[dest] == -1) {
        printf("%d", dest + 1);
        return;
    }

    printPath(parent, parent[dest]);
    printf(" -> %d", dest + 1);
}

// Function to print the result
void printResult(int src, int dest, int dist[], int parent[], char cities[][20]) {
    printf("Minimum cost from %s to %s: %d\n", cities[src], cities[dest], dist[dest]);
    printf("Route: ");
    printPath(parent, dest);
    printf("\n");
}

// Dijkstra's Algorithm
void dijkstra(int graph[MAX_CITIES][MAX_CITIES], int V, int src, int dest, char cities[][20]) {
    int dist[MAX_CITIES];
    bool visited[MAX_CITIES];
    int parent[MAX_CITIES];

    // Initialize dist, visited, and parent arrays
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printResult(src, dest, dist, parent, cities);
}

int main() {
    char cities[MAX_CITIES][20] = {"City A", "City B", "City C", "City D", "City E"};  // Replace with your city names

    int graph[MAX_CITIES][MAX_CITIES] = {
        // Replace with your actual connections and costs
        {0, 10, 15, 0, 0},
        {10, 0, 30, 40, 0},
        {15, 30, 0, 0, 20},
        {0, 40, 0, 0, 25},
        {0, 0, 20, 25, 0}
    };

    int src_choice, dest_choice;

    while (true) {
        printf("Cities:\n");
        for (int i = 0; i < MAX_CITIES; i++) {
            printf("%d. %s\n", i + 1, cities[i]);
        }

        printf("Enter the source city (1-%d): ", MAX_CITIES);
        scanf("%d", &src_choice);
        printf("Enter the destination city (1-%d): ", MAX_CITIES);
        scanf("%d", &dest_choice);

        int src = src_choice - 1;
        int dest = dest_choice - 1;

        if (src < 0 || src >= MAX_CITIES || dest < 0 || dest >= MAX_CITIES) {
            printf("Invalid input. Please try again.\n");
            continue;
        }

        dijkstra(graph, MAX_CITIES, src, dest, cities);

        char another_query[10];
        printf("Do you want to find another route? (yes/no): ");
        scanf("%s", another_query);

        if (strcmp(another_query, "yes") != 0) {
            break;
        }
    }

    return 0;
}
