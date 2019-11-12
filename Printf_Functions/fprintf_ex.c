#include <stdio.h>

int main() {

    FILE *f;

    f = fopen("myfile.txt", "w");
    fprintf(f, "%s %s %s %s", "Hello", "I am", "Tuan", ".");
    fclose(f);
    return 0;

}