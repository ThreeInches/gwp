#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    umask(0);
    int fd = -1;
    //close(1);
    fd = open("./test3.txt", O_RDWR|O_CREAT, 0777);
    if(fd < 0)
    {
        perror("open error");
        return -1;
    }
    dup2(fd, 1);
    printf("fd = %d\n", fd);
    return 0;
}

