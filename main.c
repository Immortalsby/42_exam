#include "get_next_line.h"
#include <stdio.h>

int main()
{
    char **line;
    int r;

    while ((r = get_next_line(line)) > 0)
    {
        printf("%2d-%s\n---\n", r, *line);
        free(*line);
    }
    if (r >= 0)
        printf("%2d-%s\n---\n", r, *line);
    return (0);
}
