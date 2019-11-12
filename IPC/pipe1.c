#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void) {
    char write_msg[BUFFER_SIZE] = "Greetings";
    char read_msg[BUFFER_SIZE];
    int fd1[2];
    pid_t pid;

    /* Create the pipe*/
    if(pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    /* Create a child process */
    pid = fork();

    if (pid < 0) { /* Fail to create a child process */
        fprintf(stderr, "Fork failed");
        return 1;
    }

    if (pid > 0) { /* Parent Process */
        /* Close the unused end of the pipe*/
        close(fd[READ_END]);

        /* Write to the pipe */
        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);

        /* Close write end after used */
        close(fd[WRITE_END]);

        wait(NULL); // Wait for the child process to end
        printf("Child process has completed its job\n");
    }
    else { /* Child process */
        /* Close the unused end of the pipe */
        close(fd[WRITE_END]);

        /* Read from the pipe */
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("Read from Child process: %s\n", read_msg);

        /* Close the read end after used */
        close(fd[READ_END]);
    }
    return 0;

}