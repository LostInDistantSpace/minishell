/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:22:52 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/19 15:27:27 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token, int size)
{
	while (--size >= 0)
		free(token->value[size]);
	free(token->value);
	free(token);
}

void	free_env(t_env *env)
{
	t_env	*tmp_env;

	while (env)
	{
		tmp_env = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp_env;
	}
}

void	free_tokens(t_token *token)
{
	int		size;
	t_token	*tmp_token;

	while (token)
	{
		size = 0;
		tmp_token = token;
		if (token->next)
			token = token->next;
		else
			token = NULL;
		while (tmp_token->value[size])
			size++;
		free_array(tmp_token->value, size);
		free(tmp_token);
	}
}
