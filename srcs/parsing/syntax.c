/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:35:28 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/20 19:27:28 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token(char *str, int i)
{
	int			token;
	static char	*tokens[6] = {"|", "<", ">", "<<", ">>"};

	token = 0;
	if (!str || !str[i])
		return (NULL);
	if (str[i] == '|')
		return (tokens[0]);
	else if (str[i] == '<')
		token = 1;
	else if (str[i] == '>')
		token = 2;
	if ((str[i] == '>' || str[i] == '<') && str[i + 1] == str[i])
		token += 2;
	return (tokens[token]);
}

int	check_redir(char *line, int pos)
{
	char	redir;

	redir = line[pos];
	pos++;
	if (line[pos] == redir)
		pos++;
	else if (line[pos] == '<' || line[pos] == '>')
		return (unexpected_token(get_token(line, pos)));
	while (line[pos] && ft_iswhitespace(line[pos]))
		pos++;
	if (!line[pos] || is_spechar(line[pos]))
		return (unexpected_token(get_token(line, pos)));
	else if (is_forbiddenchar(line[pos]))
		return (char_not_handled(line[pos]));
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
			return (unexpected_token(get_token(line, pos)));
		while (line[pos] && ft_iswhitespace(line[pos]))
			pos++;
		if (!line[pos] || line[pos] == '|')
			return (unexpected_token(get_token(line, pos)));
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
		return (unexpected_token("|"));
	if (only_whitespace(str))
		return (1);
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
				return (4);
		}
		i++;
	}
	if (quote)
		return (unclosed_quote());
	return (0);
}
