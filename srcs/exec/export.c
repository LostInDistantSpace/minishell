/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:52:04 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/27 16:36:58 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_export(t_env **env)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, "_") != 0)
		{
			printf("export %s", current->key);
			if (current->value != NULL)
				printf("=\"%s\"", current->value);
			printf("\n");
		}
		current = current->next;
	}
}

void	create_var(char *var, char *key, t_env **env, t_data *data)
{
	t_env	*new_node;
	t_env	*current;
	char	*value;

	new_node = (t_env *) malloc(sizeof(t_env));
	value = get_value(var);
	if (!new_node)
		return (ft_error(data));
	new_node->key = key;
	if (value[0] == '=')
	{	
		new_node->value = ft_strdup(&value[1]);
		if (!new_node->value)
			return (ft_error(data));
	}
	else
		new_node->value = NULL;
	current = *env;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	new_node->next = NULL;
}

void	check_value(char *var, char *key, t_env *node, t_data *data)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
		{
			free(node->value);
			node->value = ft_strdup(&var[i + 1]);
			if (!node->value)
				return (free(key), ft_error(data));
			return ;
		}
		i++;
	}
}

void	check_key(char *var, t_env **env, t_data *data)
{
	t_env	*current;
	char	*key;

	key = get_key(var);
	if (!key)
		return (ft_error(data));
	if (key[0] == 0)
	{	
		*data->exit_status = 1;
		return (free(key));
	}
	current = *env;
	if (!check_key_name(key, data))
		return ;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{		
			check_value(var, key, current, data);
			return (free(key));
		}
		current = current->next;
	}
	if (!current)
		create_var(var, key, env, data);
}

void	ft_export(t_ast *node, t_data *data)
{
	int	i;

	i = 1;
	if (node->args[1] == NULL)
	{
		*data->exit_status = 0;
		return (print_export(data->env));
	}
	while (node->args[i])
	{
		*data->exit_status = 0;
		check_key(node->args[i], data->env, data);
		i++;
	}
}
