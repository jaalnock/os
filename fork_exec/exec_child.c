#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Print the received array in reverse order
    printf("Array in reverse order:\n");
    for (int i = argc - 1; i > 0; i--)
    {
        printf("%s ", argv[i]); // Print elements in reverse
    }
    printf("\n");
    return 0;
}

// gcc exec_child.c -o exec_child
// gcc exec_parent.c -o exec_parent
// ./exec_parent