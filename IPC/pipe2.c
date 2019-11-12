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
    int fd1[2]; // For communication between Parent - Child
    int fd2[2]; // For communication between Child - Grand Child

    pid_t pid_child, pid_grandchild;

    /* Create a pipe */
    if(pipe(fd1) == -1 || pipe(fd2) == -1) {
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
        pid_grandchild = fork();

        if (pid_grandchild < 0) {
            fprintf(stderr, "Failed to create a grand child process");
            return 1;
        }
        if (pid_grandchild == 0) { /* Grand child process */
            printf("------ Grand child (id %d) starts...........\n\n", getpid());
            // Close the unused end of the pipe
            close(fd1[READ_END]);

            // Write the message to the pipe
            write(fd1[WRITE_END], write_msg, strlen(write_msg) + 1);

            // Close the write end of the pipe
            close(fd1[WRITE_END]);

        } 
        else { /* Child process */
            // Wait for grand child process to complete
            wait(NULL);
            printf("------ Grand child (id %d) has completed its job\n\n", pid_grandchild);
            // Close the unused end of pipe 1
            close(fd1[WRITE_END]);

            // Read the message sent by grand child
            read(fd1[READ_END], read_msg, BUFFER_SIZE);
            printf("--- Child (id %d) | Message received from grand child: %s\n\n", getpid(), read_msg);

            // Close the read end of pipe 1
            close(fd1[READ_END]);

            // Copy message content from read_msg to write_msg
            strcpy(write_msg, read_msg);

            // close the unused end of pipe 2
            close(fd2[READ_END]);
            // Continue to send message to parent
            write(fd2[WRITE_END], write_msg, strlen(write_msg) + 1);
            // Close the write end of pipe 2
            close(fd2[WRITE_END]);

        } 
    }
    else { /* Parent Process */
        // Wait for child process to complete
        wait(NULL);
        printf("--- Child (id %d) has complete its job\n\n", pid_child);
        // Close the unused end of the pipe
        close(fd2[WRITE_END]);

        // Read the message passed from grand child via child
        read(fd2[READ_END], read_msg, BUFFER_SIZE);
        printf("Parent (id %d ) | Message received from grand child: %s\n\n", getpid(), read_msg);

        // Close the read end of the pipe
        close(fd2[READ_END]);
    }

    return 0;

}