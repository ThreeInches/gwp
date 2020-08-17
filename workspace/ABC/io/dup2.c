#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd = open("./log", O_CREAT|O_RDWR);
    if(fd < 0)
    {
        perror("open errror\n");
        return -1;
    }
    char buf[1024] = {0};
    close(1);
    dup2(fd, 1);
    while(1)
    {
        ssize_t read_size = read(0, buf, 1023);
        if(read_size < 0)
        {
            perror("read error\n");
            break;
        }
        printf("read info: %s\n", buf);
        fflush(stdout);
    }
    return 0;
}
