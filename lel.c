#include <stdio.h>
#include <string.h>

int main(){
    char lel[10] = "p/";
    char lol[10] = "p";
    printf("%d\n", strncmp(lel, lol,1));
    return 0;
}
