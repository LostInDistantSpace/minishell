/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:16:52 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/04 18:14:51 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	child_right(t_ast *node, t_data *data)
{
	int	status;
	
	data->is_child = true;
	ft_ast(node->right, data);
	status = *data->exit_status;
	exit_child(data);
}

void	child_left(t_ast *node, int pipe[2], t_data *data)
{
	int	status;
	
	data->is_child = true;
	close(pipe[0]);
	if (dup2(pipe[1], STDOUT_FILENO) == -1)
	{
		close(pipe[1]);
		free_data(data);
		exit(EXIT_FAILURE);
	}
	close(pipe[1]);
	ft_ast(node->left, data);
	status = *data->exit_status;
	exit_child(data);
}

void	fork_pipe(t_ast *node, t_data *data)
{
	pid_t	left;
	pid_t	right;
	int		fd[2];
	int		status;

	pipe(fd);
	left = fork();
	if (left == 0)
		child_left(node, fd, data);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	right = fork();
	if (right == 0)
		child_right(node, data);
	waitpid(left, &status, 0);
	waitpid(right, &status, 0);
	if (WIFEXITED(status))
		*data->exit_status = WEXITSTATUS(status);
}