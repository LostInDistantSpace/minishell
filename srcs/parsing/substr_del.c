/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:51:25 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/27 17:41:48 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_between_quote(char *str, char *copy, int *i, int *j)
{
	char	quote;

	quote = str[(*i)++];
	while (str[*i] != quote && str[*i])
		copy[(*j)++] = str[(*i)++];
}

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
			copy[j++] = str[++i];
		else if (str[i] == '"' || str[i] == '\'')
			copy_between_quote(str, copy, &i, &j);
		else
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
