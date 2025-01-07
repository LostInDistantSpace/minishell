/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:18:08 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/08 00:23:11 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_key(char *str, int *i)
{
	int		len;
	char	*var;

	len = 0;
	while (str[*i + len] && (ft_isalnum(str[*i + len]) || str[*i + len] == '_'))
		len++;
	if (!len)
	{
		var = malloc(sizeof(char));
		var[0] = 0;
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

char	*concat_var(t_env *env, char *previous, char *raw, int *i)
{
	char	*var;
	char	*result;

	(*i)++;
	var = get_var(env, copy_key(raw, i));
	printf(RED "var : %s\n" RESET_COLOR, var);
	if (!var)
		return (NULL); // error	management
	else if (!var[0])
	{
		free(var);
		result = ft_strjoin(previous, "$");
	}
	else
	{
		result = ft_strjoin(previous, var);
		free(previous);
	}
	return (result);
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

char	*expand_var(char *str, t_env *env)
{
	int		i;
	int		step;
	char	*result;

	i = 0;
	step = 0;
	result = NULL;
	while (str[i])
	{
		if (str[i] == '$' || !str[i])
		{
			result = fill_from_step(result, str, step, i);
			if (!result)
				return (free(str), NULL); //error management
			if (str[i] == '$')
				result = concat_var(env, result, str, &i);
			step = i;
		}
		else
			i++;
	}
	if (i == (int)ft_strlen(str))
		return (str);
	free(str);
	return (result);
}
