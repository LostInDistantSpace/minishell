/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:52:04 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/10 14:55:46 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_export(t_env **env)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		printf("export %s", current->key);
		if (current->value != NULL)
			printf("=\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
}

void	create_var(char *key, char *value, t_env **env, t_data *data)
{
	t_env	*new_node;
	t_env	*current;

	new_node = (t_env*)malloc(sizeof(t_env));
	if (!new_node)
		return(ft_error(data));
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	current = *env;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	new_node->next = NULL;
}

void	check_key(char *var, t_env **env, t_data *data)
{
	t_env	*current;
	char	*key;
	char	*value;

	key = get_key(var);
	value = get_value(var);
	current = *env;
	if (!key)
		return (ft_error(data));
	if (!check_key_name(key))
	{	
		printf("export: %s: not a valid identifier\n", key);
		return;
	}
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (value)
			{	
				free(current->value);
				current->value = ft_strdup(value);
				break;
			}
		}
		current = current->next;
	}
	if (!current)
		create_var(key, value, env, data);

}

void	ft_export(t_ast *node, t_data *data)
{
	int	i;

	i = 1;
	if (node->args[1] == NULL)
		return(print_export(data->env));
	while (node->args[i])
	{
		check_key(node->args[i], data->env, data);
		i++;
	}
}