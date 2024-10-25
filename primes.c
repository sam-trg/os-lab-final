// primes between two numbers
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int start, end;

int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++)
        if (num % i == 0) return 0;
    return 1;
}

void* generate_primes(void* arg) {
    for (int i = start; i <= end; i++)
        if (is_prime(i))
            printf("%d ", i);
    printf("\n");
    return NULL;
}

int main() {
    printf("Enter start and end: ");
    scanf("%d %d", &start, &end);

    pid_t pid = fork();

    if (pid == 0) { // Child process
        pthread_t thread;
        pthread_create(&thread, NULL, generate_primes, NULL);
        pthread_join(thread, NULL);
        exit(0);
    } else { // Parent process
        wait(NULL); // Wait for child to finish
    }

    return 0;
}

