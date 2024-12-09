/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:06:25 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/09 18:39:50 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	change_input(t_ast_node *node, t_data *data)
{
	if (node->right->type == TOKEN_REDIR_IN || node->right->type == TOKEN_REDIR_HEREDOC)
}

void	create_pipe(t_ast_node *node, t_data *data)
{
	pid_t	child;
	int	fd[2];

	if (pipe(fd) == -1)
		perror("No more available fd"); //idk which function to use
	child = fork();
	if (child == -1)
		perror("Fork failed");
	else if (child == 0)
	{
		close(fd[0]);
		data->save_out = dup(STDOUT_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ast(node->left, data);
	}
	else
	{
		close(fd[1]);
		data->save_in = dup(STDIN_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		ast(node->right, data);
	}
}

void	ast(t_ast_node *node, t_data *data)
{
	if (node->type == TOKEN_PIPE)
		create_pipe(node, data);
	if (node->type == TOKEN_REDIR_IN)
		change_input(node, data);
	if (node->type == TOKEN_REDIR_OUT)
		change_output(node);
	if (node->type == TOKEN_REDIR_APPEND)
		append_output(node);
	if (node->type == TOKEN_REDIR_HEREDOC)
		heredoc_input(node);
	if (node->type == TOKEN_WORD)
		exec_command(node);
}

void	init_data(t_data *data, t_ast_node **head, t_env **start)
{
	data->save_in = -123;
	data->save_out = -123;
	data->ast = head;
	data->env = start;
}

void	exec(t_ast_node **head, t_env **start)
{
	t_data	*data;

	init_data(data, head, start);
	ast(data->ast, data);
}
