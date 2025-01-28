/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:18:08 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/28 15:15:56 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Concatenates the variable if it exists to previous
** previous 
*/
char	*concat_var(t_env *env, char **array, int *i, int exit_status)
{
	char	*var;
	char	*num;
	char	*result;
	char	*previous;

	(*i)++;
	var = get_var_from_key(env, array[0], i);
	previous = array[1];
	if (!previous)
		return (free(var), NULL);
	if (var)
	{
		if (*var < 0)
			result = ft_strjoin(previous, "$");
		else if (*var == '?')
		{
			num = ft_itoa(exit_status);
			result = ft_strjoin(previous, num);
			free(num);
		}
		else
			result = ft_strjoin(previous, var);
		return (free(previous), free(var), result);
	}
	return (previous);
}

/*
** Adds substring of str from start to stop
** to the string previous
*/
char	*fill_from_step(char *prev, char *str, int start, int stop)
{
	size_t	i;
	size_t	len;
	char	*result;

	i = -1;
	len = ft_strlen(prev) + stop - start + 1;
	if (!prev || (int)len == stop - start + 1)
	{
		if (prev)
			free(prev);
		return (ft_substr(str, start, stop - start));
	}
	result = malloc(sizeof(char) * len);
	if (!result)
		return (free(prev), NULL);
	while (prev[++i])
		result[i] = prev[i];
	free(prev);
	while (start < stop)
		result[i++] = str[start++];
	result[i] = '\0';
	return (result);
}

char	*expand(char *str, t_env *env, char q, int exit_status)
{
	int		i;
	int		step;
	char	quote;
	char	*array[2];

	array[0] = str;
	i = 0;
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
				return (free(str), NULL);//error management
			step = i;
		}
		else
			i++;
	}
	array[1] = fill_from_step(array[1], str, step, i);
	return (free(str), array[1]);
}

void	clean_tokens(t_token **token, t_env *env, int exit_status)
{
	int		i;
	char	**array;
	t_token	*tok;

	tok = *token;
	while (tok)
	{
		i = 0;
		array = tok->value;
		while (array[i])
		{
			if (tok->type != WORD && tok->type != REDIR_HEREDOC
				&& tok->type != PIPE)
				array[i] = expand(array[i], env, '\'', exit_status);
			i++;
		}
		tok = tok->next;
	}
}
