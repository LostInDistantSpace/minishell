/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:04:20 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/06 17:04:52 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
	{
		if (!s1 && !s2)
			return (0);
		else if (!s1)
			return (s2[0]);
		else
			return (s1[0]);
	}
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
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

int	word_num(char *input, int pos)
{
	int		i;
	int		words;

	words = 0;
	i = pos;
	while (input[i] < 0 || ft_iswhitespace(input[i]))
		i++;
	while (input[i] && input[i] != '|')
	{
		if (input[i] > 0 && !ft_iswhitespace(input[i]))
		{
			if (i == pos || ft_iswhitespace(input[i - 1]))
				words++;
		}
		i++;
	}
	return (words);
}
