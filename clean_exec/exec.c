/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:05:03 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/17 16:23:45 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ast(t_ast *node, t_data *data)
{
	if (node->type == PIPE)
		create_pipe(node, data);
	if (node->type == REDIR_IN)
		change_input(node, data);
	if (node->type == REDIR_OUT || node->type == REDIR_APPEND)
		change_output(node, data);
	if (node->type == REDIR_HEREDOC)
		handle_heredoc(node, data);
	if (node->type == WORD)
		find_command(node, data);
}

int	init_data(t_data *data, t_ast **head, t_env **start)
{
	data->save_in = dup(STDIN_FILENO);
	if (data->save_in == -1)
	{	
		perror("Error: STDIN: couldn't duplicate file descriptor");
		return(0);
	}
	data->save_out = dup(STDOUT_FILENO);
	{	
		perror("Error: STDOUT: couldn't duplicate file descriptor");
		return(0);
	}
	data->ast = head;
	data->env = start;
	return (1);
}

void	exec(t_ast **head, t_env **start)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return(perror("Error : data: malloc failed"));
	init_data(data, head, start);
	ast(*head, data);
}