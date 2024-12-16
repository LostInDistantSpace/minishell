/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:00:07 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/16 17:21:08 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*get_var(char *var, t_data *data)
{
	t_env	*current;

	current = data->env;
	while(current)
	{
		if (ft_strncmp(&var[1], current->key, ft_strlen(current->key)) == 0)
			return (current->value);//pointer?
		current = current->next;
	}
	return (NULL);
}

t_ast	*check_key(char *key, t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current != NULL)
	{
		if (ft_strncmp(key, current->key, ft_strlen(key)) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	export(t_ast *node, t_data *data)
{
	char	**var;
	t_env	*new_node;

	var = ft_split(node->args[1], '=');
	new_node = check_key(var[0], data);
	if (!new_node)
	{	
		new_node = (t_env *)malloc(sizeof(t_env));
		new_node->key = var[0];
	}
	if (var[1][0] == '$')
		new_node->value = get_var(var[1],data);
	else
		new_node->value = var[1];
}
	