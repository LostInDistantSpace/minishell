/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:18:08 by bmouhib           #+#    #+#             */
/*   Updated: 2025/02/06 13:41:11 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*special_var(char var, char *previous, int exit_status)
{
	char	*num;
	char	*result;

	if (var == '?')
	{
		num = ft_itoa(exit_status);
		result = ft_strjoin(previous, num);
		return (free(num), result);
	}
	else
		return (ft_strdup(previous));
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

	var = get_var_from_key(env, array[0], i);
	previous = array[1];
	if (!previous)
		return (free(var), NULL);
	if (var)
	{
		if (*var < 0)
			result = ft_strjoin(previous, "$");
		else if (*var == '?' || (*var >= '0' && *var <= '9'))
			result = special_var(*var, previous, exit_status);
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
	init_expand(&array[1], &quote, &step, &i);
	while (str[i])
	{
		if (str[i] == q)
			quote = str[i] - quote;
		if (!quote && str[i] == '$')
		{
			array[1] = fill_from_step(array[1], str, step, i);
			if (q && !is_quotes(str[++i]))
				array[1] = concat_var(env, array, &i, exit_status);
			if (!array[1])
				return (free(str), NULL);
			step = i;
		}
		else
			i++;
	}
	array[1] = fill_from_step(array[1], str, step, i);
	return (free(str), array[1]);
}
