/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:36:54 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/22 11:55:41 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_command(t_ast *node, t_data *data, char *path, char **env)
{
	close(data->save_in);
	close(data->save_out);
	if (execve(path, node->args, env) == -1)
	{
		printf("%s: Command not found\n", node->args[0]);
		free_array(&env);
		free(path);
		free_data(data);
		exit(EXIT_FAILURE);
	}
}

void	fork_command(t_ast *node, t_data *data, char *path, char **env)
{
	pid_t	child;
	int		status;

	child = fork();
	status = 0;
	if (child == -1)
		return (perror(NULL));
	if (child == 0)
	{
		data->is_child = true;
		exec_command(node, data, path, env);
	}
	else
	{	
		waitpid(child, &status, 0);
		if (WIFEXITED(status))
			*data->exit_status = WEXITSTATUS(status);//check this
		else
			*data->exit_status = 0;
		free(path);
		free_array(&env);
	}
}

void	find_command(t_ast *node, t_data *data)
{
	char	**env;
	char	*path;

	if (access(node->args[0], X_OK == -1))//switch order
		path = get_path(node->args[0], data);
	else
		path = ft_strdup(node->args[0]);//switch, check if is directory/permission
	if (!path)//change, print in get_path
	{
		printf("%s: Command not found\n", node->args[0]);
		if (data->is_child == true)
			exit(EXIT_FAILURE);
		*data->exit_status = 127;
		return ;
	}
	env = get_env(data->env);
	if (!env)
		return (ft_error(data));
	if (data->is_child == false)
		fork_command(node, data, path, env);
	else
		exec_command(node, data, path, env);
}

void	handle_commands(t_ast *node, t_data *data)
{
	if (ft_strcmp(node->args[0], "echo") == 0)
		ft_echo(node, data);
	else if (ft_strcmp(node->args[0], "cd") == 0)
		ft_cd(node, data->env, data);
	else if (ft_strcmp(node->args[0], "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(node->args[0], "export") == 0)
		ft_export(node, data);
	else if (ft_strcmp(node->args[0], "unset") == 0)
		ft_unset(node, data);
	else if (ft_strcmp(node->args[0], "env") == 0)
		ft_env(data->env, data);
	else if (ft_strcmp(node->args[0], "exit") == 0)
		ft_exit(node, data);
	else
		find_command(node, data);
}
