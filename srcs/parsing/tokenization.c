/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:43:30 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/14 17:11:31 by bmouhib          ###   ########.fr       */
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

/*
Handles the words in the input string.
*/
char	*handle_word(char **s, int *pos)
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
	value = ft_substr_del(*s, *pos, i - *pos);
	*pos = i;
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
		while ((*input)[pos] && !is_spechar((*input)[pos]))
			pos++;
		if (!(*input)[pos] || (*input)[pos] == '|')
			return ;
		type = handle_redir(*input, &pos);
		if (type == -1)
			return ; // handle error
		while ((*input)[pos] && ft_iswhitespace((*input)[pos]))
			pos++;
		value = handle_word(input, &pos);
		token = new_token(value, type);
		free(value);
		add_token(head, token);
	}
}

int	handle_words(char *input, int *pos, t_token **head)
{
	int		cur_word;
	int		num_word;
	char	**array;

	num_word = word_num(input, *pos);
	if (!num_word)
		return (0);
	array = malloc((num_word + 1) * sizeof(char *));
	if (!array)
		return (-1);
	while (ft_iswhitespace(input[*pos]))
		(*pos)++;
	cur_word = 0;
	while (input[*pos] && input[*pos] != '|')
	{
		if (input[*pos] > 0 && !ft_iswhitespace(input[*pos]))
		{
			array[cur_word] = handle_word(&input, pos);
			cur_word++;
		}
		else
			(*pos)++;
	}
	array[num_word] = NULL;
	add_token(head, word_token(&array, num_word));
	return (num_word);
}

/*
 Iterates through the input, creating tokens for words separated by spaces.
*/
t_token	*tokenize_input(char *input)
{
	int		i;
	int		words_num;
	t_token	*head;

	i = 0;
	head = NULL;
	while (input[i])
	{
		handle_redirs(&input, i, &head);
		words_num = handle_words(input, &i, &head);
		if (!words_num)
		{
			while (input[i] && input[i] != '|')
				i++;
		}
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
