/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_digits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:01:29 by bmouhib           #+#    #+#             */
/*   Updated: 2024/09/10 15:19:44 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*flag_digit(char *str, int *fdigit, t_flag *flag, va_list args)
{
	int		arg;

	arg = 0;
	if (*str == '*')
	{
		arg = va_arg(args, int);
		if (arg < 0)
		{
			flag->left = 1;
			arg *= -1;
		}
		*fdigit = arg;
		return (str + 1);
	}
	*fdigit = 0;
	while (*str >= '0' && *str <= '9' && *str)
		*fdigit = *fdigit * 10 + (*str++ - '0');
	return (str);
}
