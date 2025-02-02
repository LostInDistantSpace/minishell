/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:43:30 by bmouhib           #+#    #+#             */
/*   Updated: 2025/02/02 16:45:25 by bmouhib          ###   ########.fr       */
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

void	handle_redirs(char **input, int pos, t_token **head, t_parse data)
{
	int		type;
	char	*value;
	t_token	*token;

	value = NULL;
	while ((*input)[pos] && (*input)[pos] != '|')
	{
		pos = seek_spe_char(*input, pos);
		if (!(*input)[pos] || (*input)[pos] == '|')
			return ;
		type = handle_redir(*input, &pos);
		if (type == -1)
			return ; // handle error
		while ((*input)[pos] && ft_iswhitespace((*input)[pos]))
			pos++;
		value = handle_delim(input, &pos);
		if (type != HEREDOC)
			value = expand(value, data.env, '\'', data.exit_status);
		token = new_token(value, type);
		free(value);
		add_token(head, token);
	}
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
	data = create_data(env, exit_status);
	while (input[i])
	{
		handle_redirs(&input, i, &head, data);
		words_num = handle_words(input, &i, &head, data);
		if (!words_num)
			while (input[i] && input[i] != '|')
				i++;
		else if (words_num < 0)
			return (free_tokens(&head), NULL);
		if (input[i] == '|')
		{
			add_token(&head, new_token("|", PIPE));
			i++;
		}

	}
	return (head);
}
