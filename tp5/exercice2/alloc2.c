#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "alloc.h"
#include <sys/mman.h>


struct node * alloc(void) {
    struct node* n = mmap(NULL, sizeof(struct node),
    PROT_READ | PROT_WRITE,
    MAP_PRIVATE | MAP_ANONYMOUS,
    -1, 0);
    
    return n;
}

void dealloc(struct node* n){
    munmap
}