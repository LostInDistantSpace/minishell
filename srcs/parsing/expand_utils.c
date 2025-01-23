/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:39:29 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/22 17:12:54 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Returns a copy of the key starting from position i in str
*/
char	*copy_key(char *str, int *i)
{
	int		len;
	char	*var;

	len = 0;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (str[*i + len] && (ft_isalnum(str[*i + len]) || str[*i + len] == '_'))
		len++;
	if (!len)
	{
		var = malloc(sizeof(char) * 2);
		var[0] = -1;
		var[1] = '\0';
	}
	else
	{
		var = ft_substr(str, *i, len);
		if (!var)
			return (NULL);
		*i += len;
	}
	return (var);
}

char	*get_var_from_key(t_env *env, char *raw, int *i)
{
	char	*key;
	char	*var;

	key = copy_key(raw, i);
	var = get_var(env, key);
	free(key);
	return (var);
}

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
		return (ft_substr(str, start, stop - start));
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

void	init_expand(char **result, char *quote, int *step, int *i)
{
	*i = 0;
	*step = 0;
	*quote = 0;
	*result = NULL;
}
