/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:43:32 by bmouhib           #+#    #+#             */
/*   Updated: 2025/02/04 13:47:24 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_num(const char *input)
{
	int		i;
	int		words;
	char	quote;

	i = 0;
	words = 0;
	quote = 0;
	while (input[i] && input[i] != '|')
	{
		if (!quote && !ft_iswhitespace(input[i]))
			if (i == 0 || ft_iswhitespace(input[i - 1]))
				words++;
		if (input[i] == -2)
			i++;
		else if (is_quotes(input[i]) && (i == 0 || input[i - 1] > 0))
			if (quote == input[i] || !quote)
				quote = input[i] - quote;
		i++;
	}
	return (words);
}

char	*get_words(char *input, int pos)
{
	int		i;
	char	quote;
	char	*final;
	char	*result;

	i = 0;
	result = malloc(ft_strlen(input) + 1);
	while (input[pos] && input[pos] != '|')
	{
		if (input[pos] == '"' || input[pos] == '\'')
		{
			quote = input[pos];
			result[i++] = input[pos++];
			while (input[pos] != quote && input[pos])
				result[i++] = input[pos++];
			result[i++] = input[pos];
			quote = 0;
		}
		else if (input[pos] > 0)
			result[i++] = input[pos];
		pos++;
	}
	result[i] = 0;
	final = ft_strdup(result);
	return (free(result), final);
}

char	*expand_var(char *str, t_env *env, int exit_status, int *pos)
{
	int		i;
	int		step;
	char	quote;
	char	*array[2];

	array[0] = str;
	init_expand(&array[1], &quote, &step, &i);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && (!quote || str[i] == quote))
			quote = str[i] - quote;
		if (quote != '\'' && str[i] == '$')
		{
			array[1] = fill_from_step(array[1], str, step, i);
			array[1] = concat_var(env, array, &i, exit_status);
			if (!array[1])
				return (free(str), NULL);
			step = i;
		}
		else
			i++;
	}
	array[1] = fill_from_step(array[1], str, step, i);
	(*pos) += i;
	return (free(str), array[1]);
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
	while ((*s)[i] && !ft_iswhitespace((*s)[i]))
	{
		if ((*s)[i] == -2)
			i++;
		else if ((*s)[i] == '"' || (*s)[i] == '\'')
		{
			quote = (*s)[i++];
			while ((*s)[i] != quote && (*s)[i])
				i++;
			quote = 0;
		}
		i++;
	}
	value = substr_del(*s, *pos, i - *pos);
	*pos = i;
	return (value);
}

int	handle_words(char *input, int *pos, t_token **head, t_parse data)
{
	int		i;
	int		cur_word;
	int		num_word;
	char	**array;

	i = 0;
	/*
	** PROBLEM WITH QUOTES INSIDE QUOTES
	*/
	input = expand_var(get_words(input, *pos), data.env, data.exit_status, pos);
	num_word = word_num(input);
	if (!num_word)
		return (free (input), 0);
	array = malloc((num_word + 1) * sizeof(char *));
	if (!array)
		return (-1);
	cur_word = 0;
	while (input[i] && input[i] != '|')
	{
		if ((input[i] > 0 || input[i] == -2) && !ft_iswhitespace(input[i]))
			array[cur_word++] = handle_word(&input, &i);
		else
			i++;
	}
	array[num_word] = NULL;
	add_token(head, word_token(&array, num_word));
	return (free(input), num_word);
}
