/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_in_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:53:58 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/10 18:22:19 by lemarian         ###   ########.fr       */
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

void	change_input(t_ast *node, t_data *data)//update
{
	int	fd_in;

	if (node->right->type == REDIR_IN || node->right->type == REDIR_HEREDOC)
		multiple_input(node, data);
	else
	{
		if (access(node->right->args[0], F_OK) == -1)
			perror("File does not exist");
		fd_in = open(node->right->args[0], O_RDONLY);
		if (fd_in < 0)
			perror("failed to open file");
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	find_command_node(node, data);//
}
