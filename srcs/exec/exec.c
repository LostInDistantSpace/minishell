/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:23:12 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/09 15:49:32 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_ast(t_ast *node, t_data *data)
{
	if (node->type == PIPE)
		create_pipe(node, data);
	else if (node->type == REDIR_IN || node->type == REDIR_HEREDOC)
		change_input(node, data);
	else if (node->type == REDIR_OUT || node->type == REDIR_APPEND)
		change_output(node, data);
	else if (node->type == WORD)
		handle_commands(node, data);
}

int	init_data(t_data *data, t_ast **head, t_env **start)
{
	data->save_in = dup(STDIN_FILENO);
	if (data->save_in == -1)
	{	
		perror(strerror(errno));
		return(0);
	}
	data->save_out = dup(STDOUT_FILENO);
	if (data->save_out == -1)
	{	
		perror(strerror(errno));
		return(0);
	}
	data->is_child = false;
	data->ast = head;
	data->env = start;
	return (1);
}

void	exec(t_ast **head, t_env **start)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return(perror(strerror(errno)));
	init_data(data, head, start);
	ft_ast(*head, data);
	restore_in_out(data);
}