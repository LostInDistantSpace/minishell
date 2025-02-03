/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:16:52 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/03 15:45:04 by lemarian         ###   ########.fr       */
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

void	init_child_2(t_ast *node, int fd[2], t_data *data)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		printf("child 2 fail\n");
		perror(NULL);
		free_child(data);
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	ft_ast(node->right, data);
	restore_in_out(data);
	free_data(data);
	exit(EXIT_SUCCESS);
}

void	init_child_1(t_ast *node, int fd[2], t_data *data)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[1]);
		printf("child 1 fail\n");
		perror(NULL);
		free_child(data);
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
	ft_ast(node->left, data);
	restore_in_out(data);
	free_data(data);
	exit(EXIT_SUCCESS);
}

void	fork_pipe(t_ast *node, t_data *data)
{
	pid_t	child_1;
	pid_t	child_2;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_error(data);
	child_1 = fork();
	if (child_1 == -1)
		ft_error(data);
	else if (child_1 == 0)
		init_child_1(node, fd, data);
	child_2 = fork();
	if (child_2 == -1)
		ft_error(data);
	else if (child_2 == 0)
		init_child_2(node, fd, data);
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
}
