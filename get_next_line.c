#include "get_next_line.h"


// 读一句话，"hello world\n"
// 如果读到了h，返回1，如果啥也没读到，返回0，如果读到负数了，说明
// 文件不是有效的，返回-1.

int get_next_line(char **line)
{
    int ret;
    char buf[2];

    // 先租一个空间给line， 然后让line等于\0
    if (!line || !(*line = malloc(sizeof(char) * 1)))
        return (-1);
    *line[0] = '\0';
    // 读fd中的一个字符，若读出来为负数就返回-1，若为0则返回0
    // 此处为检测fd是否为有效的fd
    if ((ret = read(0, buf, 1)) < 0)
        return (-1);
    if (ret == 0)
        return (0);
    // 此时buff里面是一个字符，所以给他设置结束符\0； 
    buf[1] = '\0';
    if (buf[0] == '\n')
        return (1);
    // 如果buff里面保存的是/n，就返回1
    *line = ft_realloc(*line, buf);
    // get_char函数只是重复上述步骤
    while ((ret = get_char(line, buf)) == 2)
        ;
    return (ret);
}
// 由于之前已经malloc一次line了，所以要重新malloc
// 这次malloc一个新的字符串new，new的长度为line+buf+1
char *ft_realloc(char *s1, char *s2)
{
    char *new;
    int i;
    int k;

    if (!(new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
        return (NULL);
    i = 0;
    // 将line的数据保存到new里
    while (s1[i])
    {
        new[i] = s1[i];
        i++;
    }
    k = 0;
    // 将buf的值写到后面
    while (s2[k])
        new[i++] = s2[k++];
    new[i] = '\0';
    // 一定记住把line给free掉；
    free(s1);
    s1 = NULL;
    return (new);
}

int get_char(char **line, char *buf)
{
    int ret;

    ret = read(0, buf, 1);
    if (ret == 0)
        return (0);
    if (buf[0] == '\n')
        return (1);
    buf[1] = '\0';
    *line = ft_realloc(*line, buf);
    return (2);
}

int ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}
