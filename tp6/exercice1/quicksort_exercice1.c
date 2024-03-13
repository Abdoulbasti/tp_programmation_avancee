#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


/*Question1
Resulatat : 
real    0m0.182s
user    0m0.177s
sys     0m0.005s
*/

/*
void
quicksort(int *a, int lo, int hi)
{
    int p;

    if(lo >= hi)
        return;

    p = partition(a, lo, hi);
    quicksort(a, lo, p);
    quicksort(a, p + 1, hi);
}

int
main(int argc, char **argv)
{
    long n;
    int *a;

    if(argc != 2)
        goto usage;

    n = strtol(argv[1], NULL, 10);
    if(n <= 0)
        goto usage;

    a = malloc(n * sizeof(int));

    unsigned long long s = 0;
    for(int i = 0; i < n; i++) {
        s = s * 6364136223846793005ULL + 1442695040888963407;
        a[i] = (int)((s >> 33) & 0x7FFFFFFF);
    }

    quicksort(a, 0, n - 1);

    for(int i = 0; i < n - 1; i++) {
        assert(a[i] <= a[i + 1]);
    }

    free(a);
    return 0;

 usage:
    printf("quicksort n\n");
    return 1;
}*/


/*Question2
Resultat : 
real    0m0.187s
user    0m0.180s
sys     0m0.007s

La performence de ceci est moindre par rapport à la premiere
*/
/*
void quicksort(int *a, int lo, int hi) {
    if(lo >= hi)
        return;

    int p = partition(a, lo, hi);
    quicksort(a, lo, p);
    quicksort(a, p + 1, hi);
}

int main(int argc, char **argv) {
    long n;
    int *a;

    if(argc != 2)
        goto usage;

    n = strtol(argv[1], NULL, 10);
    if(n <= 0)
        goto usage;

    // Utilisation de mmap pour l'allocation
    a = mmap(NULL, n * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if(a == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    unsigned long long s = 0;
    for(int i = 0; i < n; i++) {
        s = s * 6364136223846793005ULL + 1442695040888963407;
        a[i] = (int)((s >> 33) & 0x7FFFFFFF);
    }

    quicksort(a, 0, n - 1);

    for(int i = 0; i < n - 1; i++) {
        assert(a[i] <= a[i + 1]);
    }

    // Libération de la mémoire
    munmap(a, n * sizeof(int));
    return 0;

usage:
    printf("quicksort n\n");
    return 1;
}*/



/*
void quicksort(int *a, int lo, int hi) {
    if(lo >= hi)
        return;

    int p = partition(a, lo, hi);

    pid_t pid1, pid2;
    int status;

    // Création du premier processus fils pour trier la première moitié
    pid1 = fork();
    if(pid1 == 0) { // Dans le fils
        quicksort(a, lo, p);
        exit(0); // Termine le processus fils une fois trié
    }

    // Création du second processus fils pour trier la seconde moitié
    pid2 = fork();
    if(pid2 == 0) { // Dans le fils
        quicksort(a, p + 1, hi);
        exit(0); // Termine le processus fils une fois trié
    }

    // Dans le processus parent, attendre que les deux fils terminent
    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);
}*/

int
partition(int *a, int lo, int hi)
{
    int pivot = a[lo];
    int i = lo - 1;
    int j = hi + 1;
    int t;
    while(1) {
        do {
            i++;
        } while(a[i] < pivot);

        do {
            j--;
        } while(a[j] > pivot);

        if(i >= j)
            return j;

        t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
}

void quicksort(int *a, int lo, int hi) {
    if(lo >= hi)
    return;
    int p = partition(a, lo, hi);

    pid_t pid1, pid2;
    pid1 = fork();

    if (pid1 < 0) {
        perror("fork 1");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // Fils 1
        quicksort(a, lo, p);
        exit(EXIT_SUCCESS);
    } else {
        // Parent
        pid2 = fork();

        if (pid2 < 0) {
            perror("fork 2");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) {
            // Fils 2
            quicksort(a, p + 1, hi);
            exit(EXIT_SUCCESS);
        } else {
            // Parent
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
        }
    }
}


int main(int argc, char **argv) {
    long n;
    int *a;

    if(argc != 2)
        goto usage;

    n = strtol(argv[1], NULL, 10);
    if(n <= 0)
        goto usage;

    a = mmap(NULL, n * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if(a == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    unsigned long long s = 0;
    for(int i = 0; i < n; i++) {
        s = s * 6364136223846793005ULL + 1442695040888963407;
        a[i] = (int)((s >> 33) & 0x7FFFFFFF);
    }

    quicksort(a, 0, n - 1);

    for(int i = 0; i < n - 1; i++) {
        assert(a[i] <= a[i + 1]);
    }

    munmap(a, n * sizeof(int));
    return 0;

usage:
    printf("Usage: quicksort n\n");
    return 1;
}