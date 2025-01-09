/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:26:27 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/09 14:36:09 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	create_pipe(t_ast *node, t_data *data)
{
	pid_t	child;
	int		fd[2];

	if (pipe(fd) == -1)
		perror(strerror(errno));
	child = fork();
	if (child == -1)
		perror(strerror(errno));
	else if (child == 0)
	{
		data->is_child = true;
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ft_ast(node->left, data);
		// free all
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		ft_ast(node->right, data);
	}
}