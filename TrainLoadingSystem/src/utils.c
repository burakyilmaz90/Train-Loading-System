#include "C:\Users\Lenovo\OneDrive\Masaüstü\proje18\include\utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error_message(char *message)
{
    printf("Error is %s\n", message);
}

void *func_malloc(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL)
    {
        error_message("Memory allocation failed");
        return NULL;
    }
    else
    {
        return ptr;
    }
}