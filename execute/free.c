/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:30:04 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/17 15:55:42 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_ast(t_ast *node)
{
	if (!node)
		return;
	free_ast(node->right);
	free_ast(node->left);
	free_array(node->args);
	free(node->type);
	free(node);
}

void	free_env(t_env **start)
{
	t_env	*current;

	while(*start)
	{
		current = *start;
		*start = (*start)->next;
		free(current->key);
		free(current->value);
		free(current);
	}
}
