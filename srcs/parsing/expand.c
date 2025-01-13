/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:18:08 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/13 17:46:11 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(char *str, t_env *env, char q, int exit_status)
{
	int		i;
	int		step;
	char	quote;
	char	*array[2];

	array[0] = str;
	init_expand(&array[1], &quote, &step, &i);
	while (str[i])
	{
		if (str[i] == q)
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
	free(str);
	return (array[1]);
}

char	*clean_whitespace(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*result;

	i = -1;
	j = 0;
	quote = 0;
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		return (NULL);
	while (str[++i] != '\0')
	{
		if ((str[i] == quote || !quote) && (str[i] == '\'' || str[i] == '"'))
			quote = str[i] - quote;
		if (quote || !ft_iswhitespace(str[i]))
			result[j++] = str[i];
		else if (j > 0 && result[j - 1] != ' ')
			result[j++] = ' ';
	}
	if (j > 0 && result[j - 1] == ' ')
		j--;
	result[j] = '\0';
	free(str);
	str = ft_strdup(result);
	return (str);
}

void	remove_quotes(char **ptr)
{
	int		i;
	int		len;
	char	*str;
	char	*result;

	i = -1;
	len = 0;
	str = *ptr;
	while (str[++i])
	{
		if (str[i] != '\'' && str[i] != '"')
			len++;
	}
	result = malloc(sizeof(char) * (len + 1));
	len = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] != '\'' && str[i] != '"')
			result[len++] = str[i];
	}
	result[len] = 0;
	free(str);
	*ptr = result;
}

void	clean_tokens(t_token *tok, t_env *env, int exit_status)
{
	int		i;
	char	**array;

	while (tok)
	{
		i = 0;
		array = tok->value;
		while (array[i])
		{
			if (tok->type == !REDIR_HEREDOC && tok->type == !PIPE)
				array[i] = expand(array[i], env, '\'', exit_status);
			if (tok->type == WORD)
				array[i] = clean_whitespace(array[i]);
			// remove_if_needed
			remove_quotes(&array[i]);
			i++;
		}
		tok = tok->next;
	}
}
