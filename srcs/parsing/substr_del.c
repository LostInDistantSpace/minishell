/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:51:25 by bmouhib           #+#    #+#             */
/*   Updated: 2025/02/12 14:34:38 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_between_quote(char *str, char *copy, int *i, int *j)
{
	char	quote;

	quote = str[*i];
	str[(*i)++] = -1;
	while (str[*i] != quote && str[*i])
	{
		if (str[*i] == -2)
			str[(*i)++] = -1;
		copy[(*j)++] = str[*i];
		str[(*i)++] = -1;
	}
}

int	handle_quoted_word(char *str, char *copy, int *i, int *j)
{
	copy_between_quote(str, copy, i, j);
	return (1);
}

char	*copy_del(char *str, int len, int *quoted)
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
		if (str[i] == '"' || str[i] == '\'')
			*quoted = handle_quoted_word(str, copy, &i, &j);
		else
		{
			if (str[i] == -2)
				str[i++] = -1;
			copy[j++] = str[i];
		}
		str[i++] = -1;
	}
	copy[j] = 0;
	result = ft_strdup(copy);
	return (free(copy), result);
}

char	*substr_del(char *str, unsigned int start, size_t len, int *quoted)
{
	if (!str)
		return (NULL);
	if (ft_strlen(str) < start)
		return (ft_strdup(""));
	if (ft_strlen(str + start) < len)
		len = ft_strlen(str + start);
	return (copy_del(str + start, len, quoted));
}
