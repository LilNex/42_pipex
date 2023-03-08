#include <unistd.h>

int main()
{
    char *args[] = {"/bin/ls", "-l", NULL}; // arguments for the command
    char *env[] = {NULL}; // environment variables

    execve("/bin/ls", args, NULL); // execute the "ls -l" command

    return 0;
}