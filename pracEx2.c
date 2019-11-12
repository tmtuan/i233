#include <stdio.h>
#include <unistd.h>

int main()
{
    /* Fork a child process */
    fork();

    /* Fork one more child process */
    fork();

    /* Fork another child process */
    fork();
    
    return 0;
}