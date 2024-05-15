#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
    char *str;
    int fd;

    fd = open("test", O_RDONLY);
//  printf("%s", get_next_line(fd));
    while((str = get_next_line(fd)) != NULL)
    {
        printf("what you print is: %s", str);
        free(str);
        
    }
/*    while((str = get_next_line(fd)) != NULL)
    {
        printf("what you print is: %s", str);
        free(str);

    }*/
    close(fd);
}

