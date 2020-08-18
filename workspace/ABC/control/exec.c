#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char* const env[] = {"PATH = /opt/rh/devtoolset-7/root/usr/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/gwp/.local/bin:/home/gwp/bin:./", NULL};
    char* const argv[] = {"-a", "-l", NULL};
    //execl("/bin/ls", "-a", "-l", NULL);
    //execlp("ls", "-a", "-l", NULL);
    //execle("/bin/ls", "-a", "-l", NULL, env);
    //execv("/bin/ls", argv);
    //execvp("ls", argv);
    execve("/bin/ls", argv, env);
    printf("Hello,World!\n");
    return 0;
}
