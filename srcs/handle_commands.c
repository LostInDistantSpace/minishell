/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:36:54 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/08 15:06:05 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_command(t_ast *node, char *path, char **env)
{
	if (execve(path, node->args, env) == -1)
	{
		perror(strerror(errno));
		free_array(env);
		free(path);
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
				perror(strerror(errno));
				free_array(env);
				free(path);
				exit(EXIT_FAILURE);
			}
		}
		else
		{	
			wait(NULL);//use waitpid for exit status?
			restore_in_out(data);
		}
}

void	find_command(t_ast *node, t_data *data)
{
	char	**env;
	char	*path;

	env = get_env(data->env);
	if (!env)
		return (perror(strerror(errno)));//replace by exit function
	if (access(node->args[0], X_OK == -1))
		path = get_path(node->args[0], env);
	else
		path = ft_strdup(node->args[0]);
	if (data->is_child == false)
		fork_command(node, data, path, env);
	else
		exec_command(node, path, env);
}

void	handle_commands(t_ast *node, t_data *data)
{
	int	len;

	len = ft_strlen(node->args[0]);
	if (ft_strncmp(node->args[0], "echo", len) == 0)
		ft_echo(node);
	//else if (ft_strncmp(node->args[0], "cd", len) == 0)
		//need to code
	else if (ft_strncmp(node->args[0], "pwd", len) == 0)
		ft_pwd(data);
	else if (ft_strncmp(node->args[0], "export", len) == 0)
		ft_export(node, data);
	else if (ft_strncmp(node->args[0], "unset", len) == 0)
		ft_unset(node, data);
	else if (ft_strncmp(node->args[0], "env", len) == 0)
		ft_env(data->env);
	//else if (ft_strncmp(node->args[0], "exit", len) == 0)
	//	ft_exit();//need exit function
	else
		find_command(node, data);
}