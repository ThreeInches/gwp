#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    int fd = open("test.txt", O_RDONLY);
    if(fd < 0)
    {
        perror("open error\n");
        return -1;
    }
    char buf[1024];
    ssize_t read_size = read(fd, buf, 1023);
    printf("read_size: %d\tread info : %s\n", read_size, buf);
    return 0;
}
