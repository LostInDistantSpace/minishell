/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:51:25 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/23 23:13:27 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_del(char *str, int len)
{
	int		i;
	int		j;
	char	*copy;
	char	*result;

	i = 0;
	j = 0;
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	while (i < len && str[i])
	{
		if (str[i] == -2)
			i++;
		copy[j++] = str[i];
		str[i++] = -1;
	}
	copy[j] = 0;
	result = ft_strdup(copy);
	return (free(copy), result);
}

char	*substr_del(char *str, unsigned int start, size_t len)
{
	if (!str)
		return (NULL);
	if (ft_strlen(str) < start)
		return (ft_strdup(""));
	if (ft_strlen(str + start) < len)
		len = ft_strlen(str + start);
	return (copy_del(str + start, len));
}
