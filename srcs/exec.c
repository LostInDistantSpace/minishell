/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:06:25 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/17 15:56:43 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_command(t_ast *node, char **cmd, char *path, char **env)
{
	pid_t	child;
	int	status;

	child = fork();
	if (child == 0)
	{
		if (execve(path, cmd, env) == -1)
		{
			perror("Command not found");
			free_array(cmd);
			free_array(env);
			free(path);
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(child, &status, NULL);
		//return exit status, store where?

}

void	find_command(t_ast *node, t_data *data)
{
	char	**cmd;
	char	**env;
	char *path;

	if (check_built_in(node, data))
		return;
	else
	{
		get_env(data); //exit if fail to get env?
		cmd = ft_split(node->args, ' ');
		if (access(node->args, X_OK == -1))
			path = get_path(node->args[0], env);
		else
			path = ft_strdup(node->args);
		if (!path)
		{
			perror("command not found");
			free_array(cmd);
			free_array(env);
			exit(EXIT_FAILURE);
		}
		else
			exec_command(node, cmd, path, env);
	}
}

void	create_pipe(t_ast *node, t_data *data)
{
	pid_t	child;
	int	fd[2];

	if (pipe(fd) == -1)
		perror("No more available fd");
	child = fork();
	if (child == -1)
		perror("Fork failed");
	else if (child == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ast(node->left, data);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		ast(node->right, data);
	}
}

void	ast(t_ast *node, t_data *data)
{
	if (node->type == PIPE)
		create_pipe(node, data);
	if (node->type == REDIR_IN)
		change_input(node, data);
	if (node->type == REDIR_OUT || node->type == REDIR_APPEND)
		change_output(node, data);
	if (node->type == REDIR_HEREDOC)
		handle_heredoc(node, data);
	if (node->type == WORD)
		find_command(node, data);
}

void	init_data(t_data *data, t_ast **head, t_env **start)
{
	data->save_in = dup(STDIN_FILENO);
	data->save_out = dup(STDOUT_FILENO);
	data->ast = head;
	data->env = start;
}

void	exec(t_ast **head, t_env **start)
{
	t_data	*data;

	init_data(data, head, start);
	ast(head, data);
}
