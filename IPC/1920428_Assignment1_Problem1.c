/*
Student's Name: TRAN Minh Tuan
Student's ID: 1920428
Assignment 1 - Problem 1
*/
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 80
#define READ_END 0
#define WRITE_END 1

int main(void) {

    printf("Parent (id %d) starts...............\n\n", getpid());

    char write_msg[BUFFER_SIZE] = "Hello, I am your grandchild";
    char read_msg[BUFFER_SIZE];
    int fd[2]; 
    
    pid_t pid_child, pid_grandchild;

    /* Create a pipe */
    if(pipe(fd) == -1) {
        fprintf(stderr, "Failed to create pipes");
        return 1;
    }
    // ... pipe has been successfully created ...
    /* Create a child process */
    pid_child = fork();

    if ( pid_child < 0) { 
        fprintf(stderr, "Failed to create a child process");
        return 1;
    }
    if (pid_child == 0) { /* Child process */
        printf("--- Child (id %d) starts............\n\n", getpid());
        /* Create a grand child process*/
        printf("--- Child (id %d) is creating grand child...\n\n", getpid());
        pid_grandchild = fork();

        if (pid_grandchild < 0) {
            fprintf(stderr, "Failed to create a grand child process");
            return 1;
        }
        if (pid_grandchild == 0) { /* Grand child process */
            printf("------ Grand child (id %d) starts...........\n\n", getpid());
            // Close the unused end of the pipe
            close(fd[READ_END]);
            printf("------ Grand childe (id %d) is writing a message to pipe\n\n", getpid());
            // Write the message to the pipe
            write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);

            // Close the write end of the pipe
            close(fd[WRITE_END]);

        } 
        else { /* Child process */
            // Wait for grand child process to complete
            wait(NULL);
            printf("------ Grand child (id %d) has completed its job\n\n", pid_grandchild);
        } 
    }
    else { /* Parent Process */
        // Wait for child process to complete
        wait(NULL);
        printf("--- Child (id %d) has complete its job\n\n", pid_child);
        // Close the unused end of the pipe
        close(fd[WRITE_END]);

        // Read the message passed from grand child via child
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("Parent (id %d ) | Message received from grand child: %s\n\n", getpid(), read_msg);

        // Close the read end of the pipe
        close(fd[READ_END]);
    }

    return 0;

}