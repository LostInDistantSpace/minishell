/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:35:28 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/09 22:14:49 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_parenthesis(char c)
{
	if (c == '(')
		return (1);
	else if (c == ')')
		return (-1);
	return (0);
}

char	check_quote(char c, char open_quote)
{
	if (open_quote && c == open_quote)
		return (0);
	else if (!open_quote)
		return (c);
	return (open_quote);
}

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
	if (!line[pos] || line[pos] == '<' || line[pos] == '>')
		return (1);
	else if (line[pos] == '|' || line[pos] == '&')
		return (1);
	return (0);
}

int	check_pipe(char *line, int pos)
{
	pos++;
	while (line[pos] && ft_iswhitespace(line[pos]))
		pos++;
	if (!line[pos] || line[pos] == '|')
		return (1);
	return (0);
}

/*
*/
int	syntax_checker(char *line)
{
	int		i;
	int		parenthesis;
	char	open_quote;

	if (syntax_init(&line, &parenthesis, &open_quote, &i))
		return (1);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			open_quote = check_quote(line[i], open_quote);
		if (!open_quote)
		{
			if (line[i] == '(' || line[i] == ')')
				parenthesis += check_parenthesis(line[i]);
			if ((line[i] == '<' || line[i] == '>') && check_redir(line, i))
				return (1);
			if (line[i] == '|' && check_pipe(line, i))
				return (1);
		}
		i++;
	}
	if (open_quote || parenthesis)
		return (2);
	return (0);
}
