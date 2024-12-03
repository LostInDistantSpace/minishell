/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:48:17 by bmouhib           #+#    #+#             */
/*   Updated: 2024/09/10 15:19:44 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_hex(unsigned long int a, int sub, int *count)
{
	if (a >= 16)
		ft_hex(a / 16, sub, count);
	if (a % 16 >= 10)
		ft_print_c(a % 16 - 10 + 'a' - sub, count);
	else
		ft_print_c(a % 16 + '0', count);
}

void	ft_print_x(unsigned int a, int sub, t_flag flag, int *count)
{
	int		to_pad;
	char	*str;

	str = ft_xtoa(a, flag.type);
	to_pad = ft_pad_math(flag, str, a);
	if (!flag.left && (!flag.zero || flag.precision >= 0))
		ft_print_padding(to_pad, ' ', count);
	if (flag.hash && !sub && a)
		ft_print_s("0x", count);
	else if (flag.hash && sub == 32 && a)
		ft_print_s("0X", count);
	if (!flag.left && flag.zero && flag.precision < 0)
		ft_print_padding(to_pad, '0', count);
	if (flag.precision - ft_strlen(str) > 0)
		ft_print_padding(flag.precision - ft_strlen(str), '0', count);
	if (a || flag.precision)
		ft_print_s(str, count);
	if (flag.left)
		ft_print_padding(to_pad, ' ', count);
	free (str);
}

int	ft_print_p(void *a, t_flag flag, int *count)
{
	char	*str;
	char	*tmp;

	if (!a)
		str = ft_strdup("(nil)");
	else
	{
		tmp = ft_xtoa((unsigned long int)a, 'x');
		str = ft_strjoin("0x", tmp);
		free (tmp);
	}
	flag.width -= ft_strlen(str);
	if (!flag.left)
		ft_print_padding(flag.width, ' ', count);
	if ((unsigned long)a || flag.precision)
		ft_print_s(str, count);
	if (flag.left)
		ft_print_padding(flag.width, ' ', count);
	free(str);
	return (1);
}
