/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_in_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:29:59 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/27 14:38:22 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	restore_in_out(t_data *data)
{
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
}

int	change_input(t_ast *node)
{
	int	fd_in;

	fd_in = open(node->args[0], O_RDONLY);
	if (fd_in < 0)
	{	
		perror(node->args[0]);
		return (0);
	}
	if (node->type == REDIR_HEREDOC)
		unlink(node->args[0]);
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		close(fd_in);
		(perror(NULL));
		return (0);
	}
	close(fd_in);
	return (1);
}

int	change_output(t_ast *node)
{
	int	fd_out;

	if (node->type == REDIR_OUT)
		fd_out = open(node->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd_out = open(node->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out < 0)
	{	
		perror(node->args[0]);
		return (0);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		close(fd_out);
		perror(NULL);
		return (0);
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
		if (node->type == REDIR_IN || node->type == REDIR_HEREDOC)
		{	
			if (!change_input(node))
				return (ft_error(data));
		}
		else if (node->type == REDIR_OUT || node->type == REDIR_APPEND)
		{	
			if (!change_output(node))
				return (ft_error(data));
		}
		node = node->right;
	}
	if (!command)
		return ;
	handle_commands(command, data);
}
