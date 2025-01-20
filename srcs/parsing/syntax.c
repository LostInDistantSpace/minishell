/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:35:28 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/20 17:02:52 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir(char *line, int pos)
{
	char	redir;

	redir = line[pos];
	pos++;
	if (line[pos] == redir)
		pos++;
	else if (line[pos] == '<' || line[pos] == '>')
		return (1);
	while (line[pos] && ft_iswhitespace(line[pos]))
		pos++;
	if (!line[pos] || is_spechar(line[pos]) || line[pos] == '&')
		return (1);
	return (0);
}

int	check_special_char(char *line, int pos)
{
	if ((line[pos] == '<' || line[pos] == '>') && check_redir(line, pos))
		return (1);
	else if (line[pos] == '|')
	{
		pos++;
		if (!line[pos] || line[pos] == '|')
			return (1);
		while (line[pos] && ft_iswhitespace(line[pos]))
			pos++;
		if (!line[pos] || line[pos] == '|')
			return (1);
	}
	return (0);
}

int	only_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_iswhitespace(line[i]))
		i++;
	if (!line[i])
		return (1);
	return (0);
}

int	syntax_checker(char *str)
{
	int		i;
	char	quote;

	if (syntax_init(str, &quote, &i))
		return (1); //unexpected token
	if (only_whitespace(str))
		return (3);
	quote = 0;
	while (str[i])
	{
		if ((!quote || str[i] == quote) && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i] - quote;
		if (!quote)
		{
			if (is_forbiddenchar(str[i]))
				return (char_not_handled(str[i]));
			if (is_spechar(str[i]) && check_special_char(str, i))
				return (1); //unexpected token near
		}
		i++;
	}
	if (quote)
		return (2);
	return (0);
}
