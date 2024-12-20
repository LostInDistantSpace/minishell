/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_in_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:53:58 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/11 18:13:27 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_in_out(t_data *data)
{
	close(data->save_in);
	close(data->save_out);
}

void	restore_in_out(t_data *data)
{
	dup2(data->save_in, STDIN_FILENO);
	dup2(data->save_out, STDOUT_FILENO);
}

void	change_input(t_ast *node, t_data *data)
{
	int	fd_in;

	if (access(node->args, F_OK) == -1)
		perror("No such file or directory");
	fd_in = open(node->args, O_RDONLY);
	if (fd_in < 0)
	{
		perror("Permission denied");
		return;
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	if (node->right != NULL)
		ast(node->right, data);
	find_command(node->left, data);
}

void	change_output(t_ast *node, t_data *data)
{
	int	fd_out;

	if (node->type == REDIR_OUT)
		fd_out = open(node->args, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd_out = open(node->args, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out < 0)
	{
		perror("Failed to get output file");
		return;
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	if (node->right != NULL)
		ast(node->right, data);
	find_command(node->left, data);
}
