/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:35:41 by bmouhib           #+#    #+#             */
/*   Updated: 2024/09/10 15:19:44 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_parse_flag(char *str, va_list args, t_flag flag, int *count)
{
	while (!is_type(flag.type) && *str)
	{
		if (is_type(*str))
			flag.type = *str;
		if (*str == '-')
			flag_left(&flag);
		if (*str == '+')
			flag.sign = 1;
		if (*str == ' ')
			flag.space = 1;
		if (*str == '#')
			flag.hash = 1;
		if (*str == '0' && !flag.left)
			flag.zero = 1;
		if (*str == '*' || (*str >= '0' && *str <= '9'))
			str = flag_digit(str, &flag.width, &flag, args);
		else if (*str == '.')
			str = flag_digit(str + 1, &flag.precision, &flag, args);
		else
			str++;
	}
	ft_print_var(args, flag, count);
	return (str);
}

void	ft_parse(char *format, va_list args, int *count)
{
	while (*format)
	{
		if (*format == '%' && *(format + 1) && *(format + 1) != '%')
			format = ft_parse_flag(format + 1, args, init_flag(), count);
		else if (*format == '%' && *(format + 1) && *(format + 1) == '%')
		{
			ft_print_c('%', count);
			format += 2;
		}
		else
			while (*format && *format != '%')
				ft_print_c(*format++, count);
	}
}

int	ft_printf(const char *format, ...)
{
	int		printed;
	va_list	args;

	printed = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	ft_parse((char *)format, args, &printed);
	va_end(args);
	return (printed);
}
