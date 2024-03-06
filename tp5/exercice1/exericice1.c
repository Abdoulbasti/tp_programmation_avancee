//Les includes 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/time.h>
#include <sys/mman.h>

void question1(){
    



}

int main(int argc, char const *argv[])
{
    long nombreMega = strtol((char *)argv[1], NULL, 10);
    long tailleMemoire = nombreMega * 1024 * 1024;

    void *ptr = mmap(NULL, tailleMemoire,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS,
        -1, 0);
    if(ptr == MAP_FAILED){
        perror("mmap");
        exit(1);
    }
    return 0;
}
