#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

int get_next_line(char **line);
int ft_strlen(char *s);
char *ft_realloc(char *s1, char *s2);
int get_char(char **line, char *buf);

#endif
