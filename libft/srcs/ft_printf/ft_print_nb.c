/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:36:24 by bmouhib           #+#    #+#             */
/*   Updated: 2024/09/10 15:19:44 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pad_math(t_flag flag, char *num, long long nb)
{
	int	value;
	int	len;

	value = flag.width;
	len = ft_strlen(num);
	if (flag.precision || nb)
	{
		if ((flag.type == 'x' || flag.type == 'X') && flag.hash && nb)
			value -= 2;
		if (flag.precision < len)
			value -= ft_strlen(num);
		else
			value -= flag.precision;
	}
	value -= (nb < 0 || flag.sign || flag.space);
	return (value);
}

void	ft_print_nb(long long int nb, t_flag flag, int *count)
{
	int		to_pad;
	char	fill;
	char	*num;

	fill = ' ';
	if (flag.zero && !flag.left && flag.precision < 0)
		fill = '0';
	num = ft_itoa_printf(nb);
	to_pad = ft_pad_math(flag, num, nb);
	if (flag.zero && flag.precision < 0 && !flag.left)
		ft_print_sign(flag, nb, count);
	if (!flag.left)
		ft_print_padding(to_pad, fill, count);
	if (flag.left || !flag.zero || flag.precision >= 0)
		ft_print_sign(flag, nb, count);
	if (flag.precision - ft_strlen(num) > 0)
		ft_print_padding(flag.precision - ft_strlen(num), '0', count);
	if (nb || flag.precision)
		ft_print_s(num, count);
	if (flag.left)
		ft_print_padding(to_pad, fill, count);
	free(num);
}
