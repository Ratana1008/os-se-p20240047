#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

// Global flag — volatile so the compiler doesn't optimize away
// changes made inside the signal handler
volatile int keep_running = 1;

// ─── Signal Handler ───────────────────────────────────────────────
void sig_handler(int signo) {
    if (signo == SIGINT) {
        printf("\n[SIGINT Received] Telling threads to stop...\n");
        keep_running = 0;   // Workers check this flag each loop
    }
}

// ─── Worker Thread Function ───────────────────────────────────────
void *worker(void *arg) {
    int id = *(int *)arg;

    while (keep_running) {
        printf("  [Thread %d] Running... (tid=%lu)\n", id, pthread_self());
        sleep(1);
    }

    printf("  [Thread %d] Flag cleared — exiting cleanly.\n", id);
    pthread_exit(NULL);
}

// ─── Main ─────────────────────────────────────────────────────────
int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    // Register SIGINT handler
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        fprintf(stderr, "Cannot catch SIGINT\n");
        exit(1);
    }

    printf("[Main] Starting worker threads. Press Ctrl+C to shut down.\n");

    // Spawn both worker threads
    pthread_create(&t1, NULL, worker, &id1);
    pthread_create(&t2, NULL, worker, &id2);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("[Main] All threads cleanly exited. Goodbye.\n");
    return 0;
}
