#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) { /* Error when creating a child process*/
        printf("Error when creating a child process");
        return 1;
    }
    else if (pid == 0) { /* Child process */
        execlp("/bin/ls", "ls", NULL);
        printf("LINE J\n");
    }
    else {/* parent process*/
        wait(NULL);
        printf("Child complete\n");
    }   
    return 0;
}