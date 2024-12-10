/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:49:26 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/10 23:44:21 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **first, t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	if (!*first)
	{
		*first = token;
		return ;
	}
	tmp = *first;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = token;
}

char	*copy_words(char *input, int *pos, int stop, int len)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (input[*pos] && *pos < stop)
	{
		if (input[*pos] > 0)
		{
			str[i++] = input[*pos];
			while (ft_iswhitespace(input[*pos + 1]))
				(*pos)++;
		}
		(*pos)++;
	}
	return (str);
}
