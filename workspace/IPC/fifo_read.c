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

    int fd = open("./test.fifo", O_RDONLY);
    if(fd < 0)
    {
        perror("open error");
        return -1;
    }
    while(1)
    {
        char buf[1024] = { 0 };
        int res = read(fd, buf, 1023);
        if(res < 0)
        {
            perror("read error");
            return -1;
        }
        else if(res == 0)
        {
            perror("all write closed");
            return -1;
        }
        printf("read:[%s]\n", buf);
    }
    close(fd);
    return 0;
}
