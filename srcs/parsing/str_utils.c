/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:04:20 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/21 20:13:07 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	seek_spe_char(char *input, int i)
{
	char	quote;

	quote = 0;
	while (input[i] && !is_spechar(input[i]))
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i++];
			while (input[i] != quote && input[i])
				i++;
			quote = 0;
		}
		else
			i++;
	}
	return (i);
}

int	is_spechar(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

char	*ft_double_join(char *left, char *middle, char *right)
{
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(left, middle);
	str = ft_strjoin(tmp, right);
	free(tmp);
	return (str);
}

char	*ft_substr_del(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		s[start + i] = -1;
		i++;
	}
	str[i] = '\0';
	return (str);
}
