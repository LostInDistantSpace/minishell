/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:18:08 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/27 14:30:48 by bmouhib          ###   ########.fr       */
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
		i = 0;
		while (tok->value[i])
			remove_quotes(&(tok->value[i++]));
		tok = tok->next;
	}
}
