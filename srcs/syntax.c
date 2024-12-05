/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:35:28 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/05 19:57:56 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_parenthesis(char c, int parenthesis)
{
	if (c == '(')
		return (parenthesis + 1);
	if (c == ')')
		return (parenthesis - 1);
}

char	check_quote(char c, char quote)
{
	if (quote && c == quote)
		return (0);
	else if (!quote)
		return (c);
}

int	check_redir(char *line, int *pos)
{
	char	redir;

	redir = line[*pos];
	*pos++;
	if (line[*pos] == redir)
		pos++;
	while (line[*pos] && ft_iswhitespace(line[*pos]))
		pos++;
	if (!line[*pos] || line[*pos] == '<' || line[*pos] == '>')
		return (1);
	if (line[*pos] == '|' || line[*pos] == '&')
		return (1);
	return (0);
}

int	check_pipe(char *line, int *pos)
{
	*pos++;
	while (line[*pos] && ft_iswhitespace(line[*pos]))
		*pos++;
	if (!line[*pos] || line[*pos] == '|')
		return (1);
	return (0);
}

/*
*/
int	syntax_checker(char *line)
{
	int		i;
	int		parenthesis;
	char	quote;

	if (syntax_init(&line, &parenthesis, &quote, &i))
		return (1);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			quote = check_quote(line[i], quote);
		if (!quote && (line[i] == '(' || line[i] == ')'))
			parenthesis = check_parenthesis(line[i], parenthesis);
		if (!quote && line[i] == '<' || line[i] == '>' && check_redir(line, &i))
			return (1);
		if (!quote && line[i] == '|' && check_pipe(line, &i))
			return (1);
		i++;
	}
	if (quote || parenthesis)
		return (2);
	return (0);
}
