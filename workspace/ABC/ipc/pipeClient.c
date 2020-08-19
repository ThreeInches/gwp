#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd = open("mypipe", O_WRONLY);
    if(fd < 0)
    {
        perror("open error\n");
        return 0;
    }

    char buf[1024];
    while(1)
    {
        buf[0] = 0;
        printf("press Enter # ");
        fflush(stdout);
        ssize_t read_size = read(0, buf, sizeof(buf) - 1);
        if(read_size > 0)
        {
            buf[read_size - 1] = 0;
            write(fd, buf, sizeof(buf) - 1);
        }
        else if(read_size <= 0)
        {
            perror("write error\n");
            return -1;
        }
    }
    close(fd);
    return 0;
}
