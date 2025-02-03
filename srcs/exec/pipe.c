/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:26:27 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/03 12:54:31 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_child(t_data *data)
{
	free_ast(data->ast);
	free_env(data->env);
	restore_in_out(data);
	free(data);
}

void	child_pipe(int pipe[2], t_data *data)
{
	close(pipe[0]);
	if (dup2(pipe[1], STDOUT_FILENO) == -1)
	{
		close(pipe[1]);
		free_child(data);
		exit(EXIT_FAILURE);
	}
	close(pipe[1]);
}

void	fork_pipe(t_ast *node, t_data *data)
{
	pid_t	child;
	int		fd[2];

	if (pipe(fd) == -1)
		perror(NULL);
	child = fork();
	if (child == -1)
		perror(NULL);
	else if (child == 0)
	{
		data->is_child = true;
		child_pipe(fd, data);
		ft_ast(node->left, data);
		free_child(data);
		exit(EXIT_SUCCESS);
	}
	else
	{
		data->piped = true;
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		ft_ast(node->right, data);
		wait(NULL);
	}
}
