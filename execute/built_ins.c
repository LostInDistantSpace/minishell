/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:26:07 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/20 14:41:36 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	echo(t_ast *node, t_data *data)
{
	int	i;

	if (!(ft_strncmp(node->args[1], "-n", 2)))
	{
		i = 2;
		while (node->args[i])
		{
			printf("%s", node->args[i]);
			i++;
		}
	}
	else
	{
		i = 1;
		while (node->args[i])
		{
			printf("%s", node->args[i]);
			i++;
		}
		printf("\n");
	}
}

void	pwd(t_data *data)
{
	char	*dir;
	size_t	size;

	dir = NULL;
	size = 0;
	printf("%s\n", getcwd(dir, size));
}

void	env(t_data *data)//change don't display null variables
{
	char **env;
	int	i;

	env = get_env(data);
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	free_array(env);
}

void	unset(t_ast *node, t_data *data)
{
	t_env	*current;
	t_env	*delete;
	int	len;

	current = data->env;
	len = ft_strlen(node->args[1]);
	delete = NULL;
	while (current)
	{
		if (ft_strncmp(node->args[1], current->next->key, len) == 0)
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

int	check_built_in(t_ast *node, t_data *data)//bof
{
	int	len;
	
	len = ft_strlen(node->args[0]);
	if (ft_strncmp(node->args[0], "echo", len) == 0)
		echo(node, data);
	if (ft_strncmp(node->args[0], "cd", len) == 0)
		//need to code
	if (ft_strncmp(node->args[0], "pwd", len) == 0)
		pwd(data);
	if (ft_strncmp(node->args[0], "export", len) == 0)
		export(node, data);
	if (ft_strncmp(node->args[0], "unset", len) == 0)
		unset(node, data);
	if (ft_strncmp(node->args[0], "env", len) == 0)
		env(data);
	if (ft_strncmp(node->args[0], "exit", len) == 0)
		ft_exit();//need exit function
	else
		return (0);
}
