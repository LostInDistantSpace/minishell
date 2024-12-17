/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:47:54 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/17 17:23:41 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	print_str(char *str)
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
	return (i);
}

int	print_char(char c)
{
	write(2, &c, 1);
	return (1);
}

int	call_str(char c, va_list args)
{
	int	len;

	len = 0;
	if (c == 's')
		len = print_str(va_arg(args, char *));
	va_end(args);
	return (len);
}

int	ft_print_error(const char *str, ...)
{
	va_list	args;
	int		i;
	int		printed;

	va_start(args, str);
	i = 0;
	printed = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] != '%')
		{
			print_char(str[i]);
			printed++;
		}
		else
		{
			printed = printed + call_str(str[i + 1], args);
			i++;
		}
		i++;
	}
	va_end(args);
	return (printed);
}
