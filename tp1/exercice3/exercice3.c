#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <string.h>

/*
int main(int argc, char const *argv[])
{
    int r = execlp("ls", "ls", "-l", NULL);
    if(r==-1) perror("erreur de recouvrement de processus");
    
    return 0;
}*/


int main(int argc, char const *argv[])
{
    int r = execl("/echo", "echo", "bonjour", (char *)0);
    if(r==-1) perror("erreur de recouvrement de processus");
    char *txt = "au-revoir\n";
    write(1, txt, strlen(txt));
    return 0;
}

