/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:24:59 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/09 13:54:00 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	change_input(t_ast_node *node, t_data *data)//need to close pipe if there is one
{
	int	fd_in;

	if (access(node->right->args[0], F_OK) == -1)
		perror("File does not exist");
	fd_in = open(node->right->args[0], O_RDONLY);
	if (fd_in < 0)
		perror("failed to open file");
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

void	create_pipe(t_ast_node *node, t_data *data)//handle child exit status? wait function?
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
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]); //idk
		ast(node->left, data);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]); //idk
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
	data->ast = head;
	data->env = start;
	data->save_in = -123;
	data->save_out = -123;
}

void	exec_pipe()
{
	/*
	fork
	in child
		dup stdout
		exec_ast left node
	in parent
		dup stdin
		execute ast right node
	*/
}

void	exec_command()
{
	/*
	fork
		get env
		check path
		exec
	*/
}
