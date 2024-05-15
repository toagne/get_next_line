#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    char *str;

    while((str = get_next_line(STDIN_FILENO)) != NULL)
    {
        printf("what you print is: %s", str);
        free(str);
        
    }
}

