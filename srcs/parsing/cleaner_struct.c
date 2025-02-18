/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:22:52 by bmouhib           #+#    #+#             */
/*   Updated: 2025/02/03 19:05:24 by bmouhib          ###   ########.fr       */
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

void	free_env(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = tmp;
	}
}

void	free_tokens(t_token **token)
{
	t_token	*tmp_token;

	while (*token)
	{
		tmp_token = *token;
		if ((*token)->next)
			*token = (*token)->next;
		else
			*token = NULL;
		if (tmp_token->type == HEREDOC)
			unlink(tmp_token->value[0]);
		free_array(&tmp_token->value);
		free(tmp_token);
	}
}

void	free_array(char ***array)
{
	int	i;

	i = 0;
	if (!*array)
		return ;
	while ((*array)[i])
	{
		free((*array)[i]);
		(*array)[i++] = NULL;
	}
	free(*array);
}

void	free_ast(t_ast **ast)
{
	if (!*ast)
		return ;
	if ((*ast)->left)
		free_ast(&(*ast)->left);
	if ((*ast)->right)
		free_ast(&(*ast)->right);
	free_array(&(*ast)->args);
	free(*ast);
}
