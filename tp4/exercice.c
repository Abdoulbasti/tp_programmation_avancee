#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


void testErreur(char mess[]){
    perror(mess);
    exit(0);
}

void log_daemon()
{
    int r, taille = 1024, r2; 
    char* file = "/tmp/logger";
    char buff[taille]; memset(buff, 0, taille);
    r = mkfifo(file, 0622);
    if(r==-1) testErreur("erreur mkfifo");
    //if(r<0 && errno!= EEXIST) perror("erreur mkfifo");


    r = open(file, O_RDONLY);
    if(r==-1)testErreur("erreur open");

    while (r2 = read(r, buff, sizeof(buff))>0)
    {
        write(STDOUT_FILENO, buff, r2);
    }

    if(r2 == -1) testErreur("Test read");
    close(r);
}

int main(int argc, char const *argv[])
{
    log_daemon();
    return 0;
}