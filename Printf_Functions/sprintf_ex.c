#include <stdio.h>

int main() {

    char str[80] = "";
    printf("Original string = %s\n", str);
    sprintf(str, "%s", "Hello, World\n");
    printf("New string = %s", str);
    return 0;
    
}