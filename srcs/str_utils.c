/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:04:20 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/09 23:28:39 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	if (s2 == NULL)
		return (*s1);
	if (s1 == NULL)
		return (-*s2);
	while (*s1 && *s2)
	{
		if (*s1 - *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	is_special_char(char c)
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
