#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    int fd[2];
    int r = pipe(fd); if(r==-1) perror("pipe error ");
    
    char* buff_write = "coucou";
    int taille_chaine = strlen(buff_write);
    char buff_read[taille_chaine]; memset(buff_read, 0, taille_chaine);
    r = fork();
    if(r==0){
        //Ecrire 
        write(fd[1], buff_write, taille_chaine);
        close(fd[0]);
    }
    else{
        
        int restant = 0, octets_lu = 0;

        while(taille_chaine>0){
            //Lire

            taille_chaine = taille_chaine - octets_lu;
            octets_lu = read(fd[0],buff_read, restant);
        

            //Faire la boucle de lecture 
        }
        close(fd[1]);
        close(fd);
    }

    return 0;
}



//pipebuff