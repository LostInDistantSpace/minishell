/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:22:25 by bmouhib           #+#    #+#             */
/*   Updated: 2024/09/10 15:19:44 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_c(char c, int *count)
{
	write(1, &c, 1);
	*count += 1;
}

void	ft_print_var(va_list args, t_flag flag, int *count)
{
	int	type;

	type = flag.type;
	if (type == 'c')
		ft_print_char(va_arg(args, int), flag, count);
	else if (type == 's')
		ft_print_string(va_arg(args, char *), flag, count);
	else if (type == 'p')
		ft_print_p(va_arg(args, void *), flag, count);
	else if (type == 'd' || flag.type == 'i')
		ft_print_nb((long long)va_arg(args, int), flag, count);
	else if (type == 'u')
		ft_print_u(va_arg(args, unsigned int), flag, count);
	else if (type == 'x' || flag.type == 'X')
		ft_print_x(va_arg(args, unsigned int), 'x' - type, flag, count);
}
