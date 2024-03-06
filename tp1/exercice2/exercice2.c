#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int generer_nombre_aleatoire() {
    //srand((unsigned)time(NULL)); // Réinitialiser la graine pour rand
    srand(getpid());
    printf("PID : %d, PPID : %d, Nombre aléatoire : %d\n", getpid(), getppid(), rand());
}

void question1()
{
    srand((unsigned)time(NULL));

    for (int i=0; i<10; i++){
        if(fork()==0){
            generer_nombre_aleatoire();
            exit(0);
        }
    }
    


    //Attendre la fin de tous les processus fils
    for (size_t j = 0; j < 10; j++){
        wait(NULL);
    }
    generer_nombre_aleatoire();
}

void question2(int nomGeneration)
{
    if(nomGeneration == 0){ return;}

    int pid = fork();
    if(pid == 0){
        generer_nombre_aleatoire();
        question2(nomGeneration-1);

    }
    else{
        wait(NULL);
    }
}


void question2_autre(int generation) {
    if (generation > 10) { // Condition de base pour arrêter la récursion
        return;
    }

    pid_t pid = fork(); // Création d'un processus fils

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Nous sommes dans le processus fils
        // Affichage du PID du fils, du PID du père et d'un nombre aléatoire
        printf("Génération %d: PID = %d, PPID = %d, Nombre aléatoire = %d\n", generation, getpid(), getppid(), rand() % 100);
        question2_autre(generation + 1); // Crée un descendant pour la prochaine génération
        exit(EXIT_SUCCESS); // Le fils termine son exécution après avoir créé son propre fils
    } else {
        wait(NULL); // Le père attend la fin de son fils
    }
}




int main(int argc, char const *argv[])
{
    int nombreGeneration = 10;
    generer_nombre_aleatoire();
    question2(10);

    
    /*srand(time(NULL));
    createDescendant(1);*/
    
    return 0;
}
