/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:52:04 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/08 14:07:15 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_export(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		printf("export %s", current->key);
		if (current->value != NULL)
			printf("=\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
}

void	create_var(char *key, char *value, t_data *data)
{
	t_env	*new_node;
	t_env	*current;

	new_node = (t_env*)malloc(sizeof(t_env));
	if (!new_node)
		perror(strerror(errno));//replace with exit fucntion
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	current = data->env;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	new_node->next = NULL;
}

int	check_key(char *var, t_data *data)
{
	t_env	*current;
	char	*key;
	char	*value;

	key = get_key(var);
	value = get_value(var);
	current = data->env;
	if (!check_key_name(key))
	{	
		printf("export: %s: not a valid identifier\n", key);
		return (1);
	}
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (value)
			{	
				free(current->value);
				current->value = ft_strdup(value);
			}
		}
		else
			create_var(key, value, data);
	}
}

void	export(t_ast *node, t_data *data)
{
	int	i;

	i = 1;
	if (node->args[1] == NULL)
		return(print_export(data));
	while (node->args[i])
	{
		check_key(node->args[i], data);
		i++;
	}
}