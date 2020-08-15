#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    printf("env[]:%s\n", getenv("PATH"));
    printf("env[]:%s\n", getenv("HOME"));
    printf("env[]:%s\n", getenv("SHELL"));
    return 0;
}
