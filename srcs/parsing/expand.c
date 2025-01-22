/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:18:08 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/21 16:11:40 by bmouhib          ###   ########.fr       */
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

char	*clean_whitespace(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*res;

	i = -1;
	j = 0;
	quote = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	while (str[++i] != '\0')
	{
		if ((str[i] == quote || !quote) && (str[i] == '\'' || str[i] == '"'))
			quote = str[i] - quote;
		if (quote || !ft_iswhitespace(str[i]) || (j > 0 && res[j - 1] != ' '))
			res[j++] = str[i];
	}
	if (j > 0 && res[j - 1] == ' ')
		j--;
	res[j] = '\0';
	free(str);
	str = ft_strdup(res);
	free(res);
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
		if (str[i] != '\'' && str[i] != '"')
			len++;
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

char	**clean_array(char **array)
{
	int		i;
	int		j;
	int		len;
	char	**cleaned;

	i = -1;
	len = 0;
	while (array[++i])
		if (array[i][0])
			len++;
	if (!len)
		return (free_array(&array), NULL);
	cleaned = malloc(sizeof(char *) * (len + 1));
	if (!cleaned)
		return (free_array(&array), NULL);
	cleaned[len] = 0;
	i = -1;
	j = -1;
	while (array[++i])
	{
		if (array[i][0])
			cleaned[++j] = array[i];
		else
			free_str(&array[i]);
	}
	return (free(array), cleaned);
}

void	clean_tokens(t_token **token, t_env *env, int exit_status)
{
	int		i;
	char	**array;
	t_token	*tok = *token;

	while (tok)
	{
		i = 0;
		array = tok->value;
		while (array[i])
		{
			if (tok->type == !REDIR_HEREDOC && tok->type == !PIPE)
				array[i] = expand(array[i], env, '\'', exit_status);
			if (tok->type == WORD)
				array[i] = clean_whitespace(array[i]); //only in echo
			i++;
		}
		i = 0;
		tok->value = clean_array(array);
		while (tok->value[i])
			remove_quotes(&(tok->value[i++]));
		tok = tok->next;
	}
}
