/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:43:30 by bmouhib           #+#    #+#             */
/*   Updated: 2025/02/05 18:23:39 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Handles the special characters in the input string.
*/
int	handle_redir(char *input, int *pos)
{
	int	i;
	int	type;

	i = *pos;
	type = -1;
	if (input[i] == '<' || input[i] == '>')
	{
		if (input[i] == '>')
			type = REDIR_OUT;
		else if (input[i] == '<')
			type = REDIR_IN;
		*pos += 1;
		if (input[i + 1] && input[i + 1] == input[i])
		{
			input[i + 1] = -1;
			*pos += 1;
			type += 2;
		}
		input[i] = -1;
	}
	return (type);
}

char	*handle_delim(char **s, int *pos)
{
	int		i;
	char	quote;
	char	*value;

	i = *pos;
	quote = 0;
	while ((*s)[i] && !ft_iswhitespace((*s)[i]) && !is_spechar((*s)[i]))
	{
		if ((!quote || (*s)[i] == quote) && ((*s)[i] == '"' || (*s)[i] == '\''))
		{
			quote = (*s)[i++];
			while ((*s)[i] != quote)
				i++;
			quote = 0;
		}
		i++;
	}
	value = substr_del(*s, *pos, i - *pos);
	*pos = i;
	return (value);
}

int	handle_redirs(char **input, int pos, t_token **head, t_parse data)
{
	int		type;
	char	*value;
	t_token	*token;

	value = NULL;
	while ((*input)[pos] && (*input)[pos] != '|')
	{
		pos = seek_spe_char(*input, pos);
		if (!(*input)[pos] || (*input)[pos] == '|')
			return (0);
		type = handle_redir(*input, &pos);
		while ((*input)[pos] && ft_iswhitespace((*input)[pos]))
			pos++;
		value = handle_delim(input, &pos);
		if (!value)
			return (1);
		if (type != HEREDOC)
			value = expand(value, data.env, '\'', data.exit_status);
		token = new_token(value, type);
		if (!token)
			return (1);
		add_token(head, token);
	}
	return (0);
}

/*
 Iterates through the input, creating tokens for words separated by spaces.
*/
t_token	*tokenize_input(char *input, t_env *env, int exit_status)
{
	int		i;
	int		words_num;
	t_token	*head;
	t_parse	data;

	i = 0;
	head = NULL;
	data.env = env;
	data.exit_status = exit_status;
	while (input[i])
	{
		if (handle_redirs(&input, i, &head, data))
			return (new_token(NULL, -1));
		words_num = handle_words(input, &i, &head, data);
		if (words_num < 0)
			return (free_tokens(&head), new_token(NULL, -1));
		while (!words_num && input[i] && input[i] != '|')
			i++;
		if (input[i] == '|')
		{
			add_token(&head, new_token(ft_strdup("|"), PIPE));
			i++;
		}
	}
	return (head);
}
