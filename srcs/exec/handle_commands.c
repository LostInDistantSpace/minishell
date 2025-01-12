/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:36:54 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/13 16:41:52 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_command(t_ast *node, t_data *data, char *path, char **env)
{
	if (execve(path, node->args, env) == -1)
	{
		printf("%s: Command not found\n", node->args[0]);
		free_array(env);
		free(path);
		free_data(data);
		exit (EXIT_FAILURE);
	}
}

void	fork_command(t_ast *node, t_data *data, char *path, char **env)
{
	pid_t	child;

	child = fork();
		if (child == -1)
			return (perror(strerror(errno)));
		if (child == 0)
		{
			if (execve(path, node->args, env) == -1)
			{
				printf("%s: Command not found\n", node->args[0]);
				free_array(env);
				free(path);
				free_data(data);
				exit(EXIT_FAILURE);
			}
		}
		else
		{	
			wait(NULL);//use waitpid for exit status?
			free(path);
			free_array(env);
		}
}

void	find_command(t_ast *node, t_data *data)
{
	char	**env;
	char	*path;

	env = get_env(data->env);
	if (!env)
		return (ft_error(data));
	if (access(node->args[0], X_OK == -1))	
		path = get_path(node->args[0], env);
	else
		path = ft_strdup(node->args[0]);//protect
	if (data->is_child == false)
		fork_command(node, data, path, env);
	else
		exec_command(node, data, path, env);
}

void	handle_commands(t_ast *node, t_data *data)
{
	if (ft_strcmp(node->args[0], "echo") == 0)
		ft_echo(node);
	else if (ft_strcmp(node->args[0], "cd") == 0)
		ft_cd(node, data->env, data);
	else if (ft_strcmp(node->args[0], "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(node->args[0], "export") == 0)
		ft_export(node, data);
	else if (ft_strcmp(node->args[0], "unset") == 0)
		ft_unset(node, data);
	else if (ft_strcmp(node->args[0], "env") == 0)
		ft_env(data->env);
	else if (ft_strcmp(node->args[0], "exit") == 0)
		ft_exit(data);
	else
		find_command(node, data);
}