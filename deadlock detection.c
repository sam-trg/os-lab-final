// deadlock detection
#include <stdio.h>

#define N 3 // Number of processes
#define M 3 // Number of resources

int main() {
    int allocation[N][M] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 3}}; // Allocation matrix
    int max[N][M] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}};         // Maximum matrix
    int available[M] = {3, 3, 2};                              // Available resources

    int work[M], finish[N] = {0};
    for (int i = 0; i < M; i++) work[i] = available[i];

    // Deadlock detection algorithm
    int deadlockExists = 0;
    while (1) {
        int found = 0;
        for (int i = 0; i < N; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < M; j++) {
                    if (max[i][j] - allocation[i][j] > work[j])
                        break;
                }
                if (j == M) {
                    for (int k = 0; k < M; k++) work[k] += allocation[i][k];
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) break;
    }

    // Check if there is a deadlock
    for (int i = 0; i < N; i++) {
        if (!finish[i]) {
            deadlockExists = 1;
            printf("System is in a deadlock. Process %d is deadlocked.\n", i);
        }
    }

    if (!deadlockExists) {
        printf("No deadlock detected.\n");
    }

    return 0;
}
