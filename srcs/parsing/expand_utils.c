/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:39:29 by bmouhib           #+#    #+#             */
/*   Updated: 2025/02/12 14:44:27 by bmouhib          ###   ########.fr       */
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
	if (str[*i] == '?' || (str[*i] >= '0' && str[*i] <= '9'))
		return (ft_substr(str, (*i)++, 1));
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
	int		idx;
	int		j;
	char	*key;
	char	*var;
	char	*result;

	key = copy_key(raw, i);
	var = get_var(env, key);
	free(key);
	if (!var)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(var) * 2 + 1));
	if (!result)
		return (NULL);
	idx = -1;
	j = 0;
	while (var[++idx])
	{
		if (is_spechar(var[idx]) || var[idx] == '"' || var[idx] == '\'')
			result[j++] = -2;
		result[j++] = var[idx];
	}
	result[j] = 0;
	return (free (var), result);
}

void	init_expand(char **result, char *quote, int *step, int *i)
{
	*i = 0;
	*step = 0;
	*quote = 0;
	*result = NULL;
}
