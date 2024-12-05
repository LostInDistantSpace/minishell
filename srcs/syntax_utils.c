/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:53:42 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/05 19:54:02 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_init(char **line, int *parenthesis, char *quote, int *i)
{
	*i = 0;
	*quote = 0;
	*parenthesis = 0;
	while (ft_iswhitespace(*line[*i]))
		*i++;
	if (*line[*i] == '|' || *line[*i] == '&')
		return (1);
	return (0);
}
