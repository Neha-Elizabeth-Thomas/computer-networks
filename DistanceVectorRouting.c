#include <stdio.h>

#define MAX_NODES 10
#define INF 9999

typedef struct {
    int distance[MAX_NODES];
    int next_hop[MAX_NODES];
} RoutingTable;

void distance_vector_routing(int cost_matrix[MAX_NODES][MAX_NODES], int nodes) {
    RoutingTable rt[MAX_NODES];
    int updated;
    
    // Initialize routing tables
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            rt[i].distance[j] = cost_matrix[i][j];
            rt[i].next_hop[j] = (cost_matrix[i][j] != INF && i != j) ? j : -1;
        }
    }
    
    // Distance Vector Algorithm
    do {
        updated = 0;
        for (int i = 0; i < nodes; i++) {
            for (int j = 0; j < nodes; j++) {
                for (int k = 0; k < nodes; k++) {
                    if (rt[i].distance[k] > cost_matrix[i][j] + rt[j].distance[k]) {
                        rt[i].distance[k] = cost_matrix[i][j] + rt[j].distance[k];
                        rt[i].next_hop[k] = j;
                        updated = 1;
                    }
                }
            }
        }
    } while (updated);
    
    // Print final routing tables
    for (int i = 0; i < nodes; i++) {
        printf("Routing table for router %d:\n", i);
        printf("Destination | Next Hop | Distance\n");
        for (int j = 0; j < nodes; j++) {
            printf("     %d      |     %d     |    %d\n", j, rt[i].next_hop[j], rt[i].distance[j]);
        }
        printf("\n");
    }
}

int main() {
    int nodes;
    int cost_matrix[MAX_NODES][MAX_NODES];
    
    printf("Enter the number of routers: ");
    scanf("%d", &nodes);
    
    printf("Enter the cost matrix (use %d for infinity):\n", INF);
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            scanf("%d", &cost_matrix[i][j]);
        }
    }
    
    distance_vector_routing(cost_matrix, nodes);
    return 0;
}
