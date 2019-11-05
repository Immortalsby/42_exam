/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 21:23:19 by bshi              #+#    #+#             */
/*   Updated: 2019/11/05 22:13:24 by bshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 要明白的思路，先是建立一个函数判断某个字符在不在某个字符串里
 * 之后先遍历第一个字符串s1，如果其中的每个字符都不在他里面重复，则打印
 * 这样会输出一段没有重复字符的s1。
 * 之后遍历第二个字符串s2，确定s2中的每个字符串，
 * 在s2中没有重复的情况下，在s1里也没有重复！！！
 * 打印对应字符串。
 * */


#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		if_in(char *s, char c, int index)
{
	int i;

	i = 0;
	while (i < index)
	{
		if (s[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int		main(int ac, char **av)
{
	int i;
	int len;

	i = 0;
	if (ac == 3)
	{
		while (av[1][i])
		{
			if (if_in(av[1], av[1][i], i))
				ft_putchar(av[1][i]);
			i++;
		}
		len = i;
		i = 0;
		while (av[2][i])
		{
			if (if_in(av[2], av[2][i], i))
				if(if_in(av[1], av[2][i], len))
					ft_putchar(av[2][i]);
			i++;
		}
	}
	ft_putchar('\n');
	return (0);
}

