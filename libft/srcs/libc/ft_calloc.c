/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:06:47 by bmouhib           #+#    #+#             */
/*   Updated: 2024/09/02 18:49:41 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;

	if (size * nmemb == 0)
	{
		array = malloc(0);
		return (array);
	}
	if (size > SIZE_MAX / nmemb)
		return (NULL);
	array = malloc (nmemb * size);
	if (!array)
		return (NULL);
	ft_bzero(array, size * nmemb);
	return (array);
}
