/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:23:12 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/27 14:21:32 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_ast(t_ast *node, t_data *data)
{
	if (node->type == PIPE)
		fork_pipe(node, data);
	else if (node->type == REDIR_IN || node->type == REDIR_HEREDOC)
		ft_redirect(node, data);
	else if (node->type == REDIR_OUT || node->type == REDIR_APPEND)
		ft_redirect(node, data);
	else if (node->type == WORD)
		handle_commands(node, data);
}

int	init_data(t_data *data, t_ast **head, t_env **start, int *e_status)
{
	data->save_in = dup(STDIN_FILENO);
	if (data->save_in == -1)
	{	
		perror(NULL);
		return (0);
	}
	data->save_out = dup(STDOUT_FILENO);
	if (data->save_out == -1)
	{	
		perror(NULL);
		return (0);
	}
	data->exit_status = e_status;
	data->is_child = false;
	data->piped = false;
	data->ast = head;
	data->env = start;
	return (1);
}

void	exec(t_ast **head, t_env **start, int *e_status)
{
	t_data	*data;

	printf("test\n");
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
	{
		free_ast(head);
		free_env(start);
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	if (!init_data(data, head, start, e_status))
		return (ft_error(data));//stop everything?
	ft_ast(*head, data);
	restore_in_out(data);
	free(data);
	g_signal = 0;
}
