/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:35:45 by bmouhib           #+#    #+#             */
/*   Updated: 2024/09/10 15:19:44 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_s(char *s, int *count)
{
	while (*s)
		ft_print_c(*s++, count);
}

void	ft_print_string(char *s, t_flag flag, int *count)
{
	if (!s)
	{
		if (flag.precision >= 6 || flag.precision < 0)
			ft_print_string("(null)", flag, count);
		else
			ft_print_padding(flag.width, ' ', count);
	}
	else
	{
		if (flag.precision > (int)ft_strlen(s) || flag.precision < 0)
			flag.precision = ft_strlen(s);
		if (flag.width)
			flag.width -= flag.precision;
		if (!flag.left)
			ft_print_padding(flag.width, ' ', count);
		while (*s && flag.precision--)
			ft_print_c(*s++, count);
		if (flag.left)
			ft_print_padding(flag.width, ' ', count);
	}
}
