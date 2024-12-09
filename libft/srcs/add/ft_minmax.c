/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:02:48 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/09 23:05:03 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_min(long a, long b)
{
	if (a < b)
		return (a);
	return (b);
}

long	ft_max(long a, long b)
{
	if (a > b)
		return (a);
	return (b);
}
