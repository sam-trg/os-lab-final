// sort two child processes differently
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_STR_LEN 100

void bubbleSort(char arr[][MAX_STR_LEN], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (strcmp(arr[j], arr[j+1]) > 0) {
                char temp[MAX_STR_LEN];
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j+1]);
                strcpy(arr[j+1], temp);
            }
        }
    }
}

void selectionSort(char arr[][MAX_STR_LEN], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (strcmp(arr[j], arr[min_idx]) < 0) {
                min_idx = j;
            }
        }
        char temp[MAX_STR_LEN];
        strcpy(temp, arr[min_idx]);
        strcpy(arr[min_idx], arr[i]);
        strcpy(arr[i], temp);
    }
}

int main() {
    int N;
    printf("Enter number of strings: ");
    scanf("%d", &N);
    
    char strings[N][MAX_STR_LEN];
    printf("Enter %d strings:\n", N);
    for (int i = 0; i < N; i++) {
        scanf("%s", strings[i]);
    }

    pid_t pid1 = fork();
    
    if (pid1 == 0) {  // First child process
        printf("Child 1: Bubble sorting...\n");
        bubbleSort(strings, N);
        for (int i = 0; i < N; i++) {
            printf("%s ", strings[i]);
        }
        printf("\n");
        exit(0);
    } 
    
    pid_t pid2 = fork();
    
    if (pid2 == 0) {  // Second child process
        printf("Child 2: Selection sorting...\n");
        selectionSort(strings, N);
        for (int i = 0; i < N; i++) {
            printf("%s ", strings[i]);
        }
        printf("\n");
        exit(0);
    } 
    
    int status;
    wait(&status);  // Parent waits for one child to finish
    printf("Parent: One child terminated. Exiting...\n");

    return 0;
}
