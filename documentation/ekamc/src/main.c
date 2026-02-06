#include <stdio.h>
#include <stdlib.h>

#include <my_math.h>
#include <my_print.h>

#include "useful.h"

int main(void) {
    printf("Hello, World!\n");
    useful_function(add(2, 3));

    // ub
    int x = 0x7fffffff;
    ++x;
    printf("Value after overflow: %d\n", x);

    // use after free
    int *ptr = malloc(10);
    free(ptr);
    *ptr = add(1, 2);
    printf("Value after use after free: %d\n", *ptr);

    // leak
    // int *leaked_ptr = malloc(20);
    // *leaked_ptr = 42;
    // printf("Leaked value: %d\n", *leaked_ptr);
    
    my_print("This is a message from my_print library.");

    return 0;
}
