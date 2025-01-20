/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:39:29 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/20 17:24:49 by bmouhib          ###   ########.fr       */
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

/*
** Concatenates the variable if it exists to previous
** previous 
*/
char	*concat_var(t_env *env, char **array, int *i, int exit_status)
{
	char	*var;
	char	*result;
	char	*previous;
	char	*raw;

	raw = array[0];
	(*i)++;
	var = get_var(env, copy_key(raw, i));
	previous = array[1];
	if (!previous)
		return (NULL);
	if (var)
	{
		if (var[0] < 0)
			result = ft_strjoin(previous, "$");
		else if (var[0] == '?')
			result = ft_strjoin(previous, ft_itoa(exit_status));
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
	len = ft_strlen(prev);
	result = malloc(sizeof(char) * (len + stop - start + 1));
	if (!result)
		return (free(prev), NULL);
	while (++i < len)
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
