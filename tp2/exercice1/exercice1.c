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
#include <arpa/inet.h>
#include <math.h>

void exercice1_1(){
    int y, r;
    int fd = open("compteur.dat", O_RDWR | O_CREAT, 0666);
    if(fd==-1 && errno==ENOENT)
    {
        y = 1;
        y = ntohl(y);
        write(fd, &y, sizeof(y));
    }

    r = read(fd, &y, sizeof(y));
    
    lseek(fd, 0, SEEK_SET);

    y = ntohl(y);
    y++;


    y = htonl(y);
    r = write(fd, &y, sizeof(y));
    
    close(fd);
}





void exercice1_2(){
    int pid = fork();
    if (pid==0){
        double compteurMax = pow(10, 2), compteur = 0;
        for (size_t i = 0; i < compteurMax; i++){
            exercice1_1();
        }
    }else{
        if(wait(NULL) == -1){perror("erreur de wait");}    
        int fd = open("compteur.dat", O_RDWR);
        int buff = 0;
        read(fd, &buff, sizeof(buff));
        buff = ntohl(buff);
        printf("valeur du compteur %d\n", buff);
        close(fd);
    }
}



int main(int argc, char const *argv[])
{
    //exercice1_2();
    exercice1_1();

    return 0;
}