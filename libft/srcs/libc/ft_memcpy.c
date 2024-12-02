/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:22:18 by bmouhib           #+#    #+#             */
/*   Updated: 2024/11/06 19:58:03 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*str;
	char	*str2;

	if (!dest && !src)
		return (NULL);
	str = (char *)dest;
	str2 = (char *)src;
	while (n-- > 0)
		*str++ = *str2++;
	return (dest);
}
