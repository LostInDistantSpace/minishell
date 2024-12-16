/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:49:26 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/16 22:45:19 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = malloc(2 * sizeof(char *));
	if (!token->value)
		return (free(token), NULL);
	token->value[0] = ft_strdup(value);
	token->value[1] = NULL;
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token	*word_token(char **value, int num_word)
{
	int		i;
	t_token	*token;

	if (!value || num_word <= 0)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = malloc((num_word + 1) * sizeof(char *));
	if (!token->value)
		return (free(token), NULL);
	i = -1;
	while (++i < num_word)
	{
		token->value[i] = ft_strdup(value[i]);
		if (!token->value[i])
			return (free_token(token, i), free_array(value, i), NULL);
	}
	token->value[i] = NULL;
	free_array(value, i);
	token->type = WORD;
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
