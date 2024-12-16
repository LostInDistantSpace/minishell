/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:43:30 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/16 22:42:35 by bmouhib          ###   ########.fr       */
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
char	*handle_word(char **str, int *pos)
{
	int		i;
	char	open_quote;
	char	*value;

	i = *pos;
	open_quote = 0;
	while ((*str)[i] && !ft_iswhitespace((*str)[i]) && !is_spe_char((*str)[i]))
	{
		if ((*str)[i] == '"' || (*str)[i] == '\'')
		{
			open_quote = (*str)[i];
			while ((*str)[i] != open_quote)
				i++;
			open_quote = 0;
		}
		i++;
	}
	value = ft_substr(*str, *pos, i - *pos);
	while (*pos < i)
	{
		(*str)[*pos] = -1;
		*pos += 1;
	}
	return (value);
}

void	handle_redirs(char **input, int pos, t_token **head)
{
	int		type;
	char	*value;
	t_token	*token;

	value = NULL;
	while ((*input)[pos] && (*input)[pos] != '|')
	{
		while ((*input)[pos] && !is_spe_char((*input)[pos]))
			pos++;
		if (!(*input)[pos] || (*input)[pos] == '|')
			return ;
		type = handle_redir(*input, &pos); //check if -1
		while ((*input)[pos] && ft_iswhitespace((*input)[pos]))
		{
			(*input)[pos] = -1;
			pos++;
		}
		value = handle_word(input, &pos);
		token = new_token(value, type);
		free(value);
		add_token(head, token);
	}
}

void	handle_words(char *input, int *pos, t_token **head)
{
	int		cur_word;
	int		num_word;
	char	**array;

	num_word = word_num(input, *pos);
	if (!num_word)
		return ;
	array = malloc((num_word + 1) * sizeof(char *));
	if (!array)
		return ; // error management
	array[num_word] = NULL;
	while (input[*pos] < 0 || ft_iswhitespace(input[*pos]))
		(*pos)++;
	cur_word = 0;
	while (input[*pos] && input[*pos] != '|')
	{
		if (input[*pos] > 0 && !ft_iswhitespace(input[*pos]))
			array[cur_word++] = handle_word(&input, pos);
		else
			(*pos)++;
	}
	add_token(head, word_token(array, num_word));
}

/*
 Iterates through the input, creating tokens for words separated by spaces.
*/
t_token	*tokenize_input(char *input)
{
	int		i;
	t_token	*head;

	i = 0;
	head = NULL;
	while (input[i])
	{
		handle_redirs(&input, i, &head);
		handle_words(input, &i, &head);
		if (input[i] == '|')
		{
			add_token(&head, new_token("|", PIPE));
			i++;
		}
	}
	return (head);
}
