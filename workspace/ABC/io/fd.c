#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    umask(0);
    close(0);
    //close(1);
    close(2);
    int fd = open("test1.txt", O_CREAT|O_WRONLY, 0644);
    if(fd < 0)
    {
        perror("open error\n");
        return -1;
    }
    char* msg = "Hello, World!";
    write(fd, msg, strlen(msg));
    printf("fd = %d\n", fd);
    close(fd);
    return 0;
}
