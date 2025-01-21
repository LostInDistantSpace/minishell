/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:43:32 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/21 22:35:26 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_num(char *input, int pos)
{
	int		i;
	int		words;
	char	quote;

	i = pos;
	words = 0;
	quote = 0;
	while (input[i] && input[i] != '|')
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (!quote && (i == 0 || (i > 0 && ft_iswhitespace(input[i - 1]))))
				words++;
			if (!quote || quote == input[i])
				quote = input[i] - quote;
		}
		else if (!quote && input[i] > 0 && !ft_iswhitespace(input[i]))
		{
			if (i == pos || ft_iswhitespace(input[i - 1]))
				words++;
		}
		i++;
	}
	return (words);
}

char	*expand_var(char *str, t_env *env, int exit_status)
{
	int		i;
	int		step;
	char	quote;
	char	*array[2];

	array[0] = str;
	init_expand(&array[1], &quote, &step, &i);
	while (str[i])
	{
		if (str[i] == '\'')
			quote = str[i] - quote;
		if (!quote && str[i] == '$')
		{
			array[1] = fill_from_step(array[1], str, step, i);
			array[1] = concat_var(env, array, &i, exit_status);
			if (!array[1])
				return (free(str), NULL); //error management
			step = i;
		}
		else
			i++;
	}
	array[1] = fill_from_step(array[1], str, step, i);
	return (free(str), array[1]);
}

char	*get_words(char *input, int pos)
{
	int		i;
	char	*tmp;
	char	*result;

	i = 0;
	result = malloc(ft_strlen(input) + 1);
	while (input[pos] && input[pos] != '|')
	{
		if (input[pos] > 0)
			result[i++] = input[pos];
		pos++;
	}
	result[i] = 0;
	tmp = ft_strdup(result);
	return (free(result), tmp);
}

int	handle_words(char *input, int *pos, t_token **head, t_parse data)
{
	int		cur_word;
	int		num_word;
	char	**array;

	input = expand_var(get_words(input, *pos), data.env, data.exit_status);
	num_word = word_num(input, *pos);
	if (!num_word)
		return (0);
	array = malloc((num_word + 1) * sizeof(char *));
	if (!array)
		return (-1);
	cur_word = 0;
	while (input[*pos] && input[*pos] != '|')
	{
		if (input[*pos] > 0 && !ft_iswhitespace(input[*pos]))
			array[cur_word++] = handle_word(&input, pos);
		else
			(*pos)++;
	}
	array[num_word] = NULL;
	add_token(head, word_token(&array, num_word));
	return (num_word);
}
