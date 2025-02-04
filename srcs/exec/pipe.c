/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:16:52 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/04 13:04:55 by lemarian         ###   ########.fr       */
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
	int	status;
	
	data->is_child = true;
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		perror(NULL);
		free_child(data);
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	close(fd[1]);
	ft_ast(node->right, data);
	restore_in_out(data);
	status = *data->exit_status;
	free_data(data);
	printf("2 dead\n");
	exit(status);
}

void	init_child_1(t_ast *node, int fd[2], t_data *data)
{
	int	status;
	
	data->is_child = true;
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[1]);
		perror(NULL);
		free_child(data);
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
	close(fd[0]);
	ft_ast(node->left, data);
	restore_in_out(data);
	status = *data->exit_status;
	free_data(data);
	printf("1 dead\n");
	exit(status);
}

void	fork_pipe(t_ast *node, t_data *data)
{
	pid_t	child_1;
	pid_t	child_2;
	int		fd[2];
	int		status;
	int		status2;

	status = 0;
	status2 = 0;
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
	if (child_1 > 0)
		waitpid(child_1, NULL, 0);
	if (WIFEXITED(status))
		*data->exit_status = WEXITSTATUS(status);
	else
		*data->exit_status = 0;
	if (child_2 > 0)
		waitpid(child_2, &status2, 0);
	if (WIFEXITED(status2))
		*data->exit_status = WEXITSTATUS(status2);
	else
		*data->exit_status = 0;
}
