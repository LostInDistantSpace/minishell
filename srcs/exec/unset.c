/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:04:00 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/06 14:21:50 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	delete_var(char *key, t_env **env)
{
	t_env	*current;
	t_env	*delete;

	current = *env;
	delete = NULL;
	while (current)
	{
		if (current->next && ft_strcmp(key, current->next->key) == 0)
		{
			delete = current->next;
			current->next = current->next->next;
			free(delete->key);
			free(delete->value);
			free(delete);
		}
		current = current->next;
	}
}

void	ft_unset(t_ast *node, t_data *data)
{
	int	i;

	i = 1;
	*data->exit_status = 0;
	if (node->args[i] == NULL)
		return ;
	while (node->args[i])
	{
		delete_var(node->args[i], data->env);
		i++;
	}
}
