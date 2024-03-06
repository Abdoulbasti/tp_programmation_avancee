#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "alloc.h"

struct node * alloc(void) {
    struct node* n = calloc(1, sizeof(struct node));
    return n;
}

void dealloc(struct node* n){
        free(n);
}