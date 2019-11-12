#include <stdio.h>

int main() {

    int a = 10;
    int *b;

    printf("Value of a = %d\n", a);
    printf("Address of a = Ox%x\n", &a);

    b = &a;
    printf("The value that p is pointing at = %d\n", *b);
    printf("Address of b = 0x%x\n", &b);
    printf("The value that b is holding = 0x%x\n", b);
    
    return 0;
}