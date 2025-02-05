/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:47:54 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/05 17:53:06 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_str(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		str = "(null)";
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

void	print_char(char c)
{
	write(2, &c, 1);
}

void	call_str(char c, va_list args)
{
	if (c == 's')
		print_str(va_arg(args, char *));
	va_end(args);
}

void	ft_print_error(const char *str, ...)
{
	va_list	args;
	int		i;

	va_start(args, str);
	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] != '%')
			print_char(str[i]);
		else
		{	
			call_str(str[i + 1], args);
			i++;
		}
		i++;
	}
	va_end(args);
}
