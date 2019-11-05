/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 22:27:59 by bshi              #+#    #+#             */
/*   Updated: 2019/11/05 23:03:52 by bshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 和union类似，如果s1的字符在s1里没有重复，并且在s2里重复了。则打印
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
	while (s[i] && (i < index || index == -1))
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

	i = 0;
	if (ac == 3)
	{
		while (av[1][i])
		{	
			if (if_in(av[1], av[1][i], i) && !if_in(av[2], av[1][i], -1))
				ft_putchar(av[1][i]);
			i++;
		}
	}
	ft_putchar('\n');
	return (0);
}
