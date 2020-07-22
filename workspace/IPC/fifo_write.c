#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
    umask(0);
    int ret = mkfifo("./test.fifo", 0664);
    if(ret < 0 && errno != EEXIST)
    {
        perror("mkfifo error");
        return -1;
    }

    int fd = open("./test.fifo", O_WRONLY);
    if(fd < 0)
    {
        perror("open error");
        return -1;
    }
    int i = 0;
    while(1)
    {
        char buf[1024] = { 0 };
        sprintf(buf, "This is a fifo example %d", i++);
        write(fd, buf, strlen(buf));
        printf("write success\n");
        sleep(1);
    }
    close(fd);
    return 0;
}

