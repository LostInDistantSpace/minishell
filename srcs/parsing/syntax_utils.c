/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:53:42 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/16 15:57:15 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_init(char *line, char *quote, int *pos)
{
	int	i;

	i = *pos;
	i = 0;
	*quote = 0;
	while (ft_iswhitespace(line[i]))
		i++;
	if (line[i] == '|' || line[i] == '&')
		return (1);
	*pos = i;
	return (0);
}

int	is_forbiddenchar(char c)
{
	if (c == '\\' || c == ';' || c == '&')
		return (1);
	return (0);
}
