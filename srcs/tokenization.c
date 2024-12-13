/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:43:30 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/13 17:32:05 by bmouhib          ###   ########.fr       */
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
		if (input[i + 1] && input[i + 1] == input[i])
		{
			input[i + 1] = -1;
			*pos += 1;
			type += 2;
		}
		*pos += 1;
		input[i] = -1;
	}
	return (type);
}

/*
Handles the words in the input string.
*/
t_token	*handle_word(char **input, int *pos, int type)
{
	int		i;
	char	*value;

	i = *pos;
	while (!ft_iswhitespace((*input)[i]) && !is_special_char((*input)[i])
		&& (*input)[i])
		i++;
	value = ft_substr(*input, *pos, i - *pos);
	while (*pos < i)
	{
		(*input)[*pos] = -1;
		*pos += 1;
	}
	return (new_token(value, type));
}

void	handle_redirs(char **input, int pos, int len, t_token **head)
{
	int		type;
	char	*value;

	value = NULL;
	while ((*input)[pos] && (*input)[pos] != '|' && pos < len)
	{
		while ((*input)[pos] && !is_special_char((*input)[pos]))
			pos++;
		if (!(*input)[pos] || (*input)[pos] == '|')
			return ;
		type = handle_redir(*input, &pos); //check if -1
		while ((*input)[pos] && ft_iswhitespace((*input)[pos]))
		{
			(*input)[pos] = -1;
			pos++;
		}
		add_token(head, handle_word(input, &pos, type));
	}
}

void	handle_words(char *input, int *pos, t_token **head)
{
	int		i;
	int		len;
	char	*str;

	i = *pos;
	len = 0;
	while (input[i] && input[i] != '|')
	{
		if (input[i] > 0)
		{
			len++;
			while (ft_iswhitespace(input[i + 1]))
				i++;
		}
		i++;
	}
	str = copy_words(input, pos, i, len);
	if (!str)
		return ;
	add_token(head, new_token(str, WORD));
}

/*
 Iterates through the input, creating tokens for words separated by spaces.
*/
t_token	*tokenize_input(char *input)
{
	int		i;
	int		len;
	t_token	*head;

	i = 0;
	len = ft_strlen(input);
	head = NULL;
	while (input[i] && i < len)
	{
		handle_redirs(&input, i, len, &head);
		handle_words(input, &i, &head);
		if (input[i] == '|')
		{
			add_token(&head, new_token("|", PIPE));
			i++;
		}
	}
	return (head);
}
