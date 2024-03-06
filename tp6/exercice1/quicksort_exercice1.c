#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <assert.h>


int partition(int *a, int lo, int hi)
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

void quicksort(int *a, int lo, int hi)
{
    int p;

    if(lo >= hi)
        return;

    p = partition(a, lo, hi);
    quicksort(a, lo, p);
    quicksort(a, p + 1, hi);
}

int main(int argc, char **argv)
{
    long n;
    int *a;

    if(argc != 2)
        goto usage;

    n = strtol(argv[1], NULL, 10);
    if(n <= 0)
        goto usage;

    //a = malloc(n * sizeof(int));
    int taille_zone_memoire = n * sizeof(int);
    void* b = mmap(
        NULL,
        taille_zone_memoire,
        PROT_READ | PROT_WRITE, 
        MAP_ANONYMOUS | MAP_SHARED,
        -1, 0
    );
    if(b == MAP_FAILED){   perror("mmap"); exit(EXIT_FAILURE); }

    //Casting
    a = (int *)b;

    unsigned long long s = 0;
    for(int i = 0; i < n; i++) {
        s = s * 6364136223846793005ULL + 1442695040888963407;
        a[i] = (int)((s >> 33) & 0x7FFFFFFF);
    }

    quicksort(a, 0, n - 1);

    for(int i = 0; i < n - 1; i++) {
        assert(a[i] <= a[i + 1]);
    }

    //free(a);
    int ret = munmap( b, taille_zone_memoire);
    if(ret == -1){  perror("munmap");   exit(EXIT_FAILURE); }

    return 0;

 usage:
    printf("quicksort n\n");
    return 1;
}