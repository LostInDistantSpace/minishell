/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:04:29 by bmouhib           #+#    #+#             */
/*   Updated: 2024/09/10 15:19:44 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	in_string(char c, char *str)
{
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
		if (!str)
			return (0);
	}
	return (0);
}

int	is_type(char c)
{
	if (in_string(c, "cspdiuxX"))
		return (1);
	return (0);
}

int	type_is_num(int type)
{
	if (in_string(type, "diuxX"))
		return (1);
	return (0);
}

t_flag	init_flag(void)
{
	t_flag	flag;

	flag.left = 0;
	flag.sign = 0;
	flag.space = 0;
	flag.hash = 0;
	flag.zero = 0;
	flag.width = 0;
	flag.precision = -1;
	flag.type = 0;
	return (flag);
}

void	flag_left(t_flag *flag)
{
	flag->left = 1;
	flag->zero = 0;
}
