/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:16:29 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/19 14:55:42 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	create_pipe(t_ast *node, t_data *data)
{
	pid_t	child;
	int	fd[2];

	data->pipe = true;
	if (pipe(fd) == -1)
		perror(strerror(errno));
	child = fork();
	if (child == -1)
		return(perror(strerror(errno)));
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