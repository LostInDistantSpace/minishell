/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:49:26 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/13 17:47:21 by bmouhib          ###   ########.fr       */
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
	while ((input[*pos] < 0 || ft_iswhitespace(input[*pos])) && *pos < stop)
		(*pos)++;
	while (input[*pos] && *pos < stop)
	{
		if (input[*pos] > 0)
		{
			str[i++] = input[*pos];
			if (ft_iswhitespace(input[*pos]))
			{
				while (ft_iswhitespace(input[*pos + 1]) && *pos < stop - 1)
					(*pos)++;
			}
		}
		(*pos)++;
	}
	return (str);
}
