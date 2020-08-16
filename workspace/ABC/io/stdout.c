#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char* msg = "Hello,world!\n";
    fwrite(msg, strlen(msg), 1, stdout);
    printf("Hello,world!\n");
    fprintf(stdout, "Hello,world!\n");
    return 0;
}
