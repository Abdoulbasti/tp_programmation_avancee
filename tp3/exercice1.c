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

void question1(){
    int fd = open("file", O_RDWR | O_CREAT, 0666);
    int fd2 = open("file", O_RDWR | O_CREAT, 0666);
    write(fd, "a", 1);
    write(fd2, "b", 1);

    fd = open("file", O_RDWR | O_CREAT, 0666);
    fd2 = dup(fd);
    write(fd, "a", 1);
    write(fd2, "b", 1);
}

int main(int argc, char const *argv[])
{
    question1();
    return 0;
}
