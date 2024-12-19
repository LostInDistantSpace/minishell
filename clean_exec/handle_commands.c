/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:15:13 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/19 15:50:48 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_command(t_ast *node, char **cmd, char *path, char **env)
{
	pid_t	child;
	int	status;

	child = fork();
	if (child == -1)
		return (perror(strerror(errno)));
	if (child == 0)
	{
		if (execve(path, cmd, env) == -1)
		{
			perror(strerror(errno));
			free_array(env);
			free(path);
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(child, &status, NULL);
		//store exit status where?
}

void	find_exec(t_ast *node, t_data *data)
{
	char	**cmd;
	char	**env;
	char *path;


	if (!get_env(data))
		return (perror(strerror(errno)));
	if (access(node->args[0], X_OK == -1))
		path = get_path(node->args[0], env);
	else
		path = ft_strdup(node->args[0]);
	if (!path)
	{
		perror(strerror(errno));
		free_array(env);
		exit(EXIT_FAILURE);//child?
	}
	else
		exec_command(node, cmd, path, env);
	
}

void	handle_commands(t_ast *node, t_data *data)
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
		find_exec(node, data);
}