#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    FILE* fp = fopen("write.txt", "r");
    if(!fp)
    {
        perror("fopen error\n");
        return -1;
    }
    char* buf[1024];
    char* msg = "Hello, World!\n";
    size_t read_size = fread(buf, 1023, 1, fp);
    printf("read_size: %d, read info: %s", read_size, buf);
    fclose(fp);
    return 0;
}
