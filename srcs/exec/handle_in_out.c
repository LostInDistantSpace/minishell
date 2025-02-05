/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_in_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:29:59 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/05 15:51:08 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	restore_in_out(t_data *data)
{
	if (data->save_in == -42)
		return ;
	if (dup2(data->save_in, STDIN_FILENO) == -1)
	{	
		close(data->save_out);
		return (ft_error(data));
	}
	if (dup2(data->save_out, STDOUT_FILENO) == -1)
	{
		close(data->save_in);
		return (ft_error(data));
	}
	close(data->save_in);
	close(data->save_out);
	data->save_in = -42;
	data->save_out = -42;
}

int	change_input(t_ast *node, t_data *data)
{
	int	fd_in;

	fd_in = open(node->args[0], O_RDONLY);
	if (fd_in < 0)
	{	
		print_error(node->args[0], strerror(errno), data);
		*data->exit_status = 1;
		return (0);
	}
	if (node->type == HEREDOC)
		unlink(node->args[0]);
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		close(fd_in);
		ft_error(data);
	}
	close(fd_in);
	return (1);
}

int	change_output(t_ast *node, t_data *data)
{
	int	fd_out;

	if (node->type == REDIR_OUT)
		fd_out = open(node->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd_out = open(node->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out < 0)
	{	
		print_error(node->args[0], strerror(errno), data);
		*data->exit_status = 1;
		return (0);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		close(fd_out);
		ft_error(data);
	}
	close(fd_out);
	return (1);
}

void	ft_redirect(t_ast *node, t_data *data)
{
	t_ast	*command;

	command = node->left;
	while (node)
	{
		if (node->type == REDIR_IN || node->type == HEREDOC)
		{	
			if (!change_input(node, data))
				return (exit_child(data));
		}
		else if (node->type == REDIR_OUT || node->type == APPEND)
		{	
			if (!change_output(node, data))
				return (exit_child(data));
		}
		node = node->right;
	}
	if (!command)
		return ;
	handle_commands(command, data);
}
