/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:16:52 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/11 17:43:55 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_right(t_ast *node, t_data *data, int fd[2])
{
	data->is_child = true;
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		*data->exit_status = 1;
		exit_child(data);
	}
	close(fd[0]);
	ft_ast(node->right, data);
	exit_child(data);
}

void	init_left(t_ast *node, t_data *data, int fd[2])
{
	data->is_child = true;
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[1]);
		*data->exit_status = 1;
		exit_child(data);
	}
	close(fd[1]);
	ft_ast(node->left, data);
	exit_child(data);
}

void	fork_pipe(t_ast *node, t_data *data)
{
	pid_t	left;
	pid_t	right;
	int		fd[2];
	int		status;

	status = 0;
	if (pipe(fd) == -1)
		ft_error(data);
	left = fork();
	if (left == -1)
		ft_error(data);
	if (left == 0)
		init_left(node, data, fd);
	right = fork();
	if (right == -1)
		ft_error(data);
	if (right == 0)
		init_right(node, data, fd);
	close(fd[0]);
	close(fd[1]);
	(waitpid(left, &status, 0), waitpid(right, &status, 0));
	if (WIFEXITED(status))
		*data->exit_status = WEXITSTATUS(status);
}
