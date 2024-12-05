/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:24:59 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/04 17:43:02 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ast(t_ast_node *node)
{
	/*
	if else statements calling a function for each token type
	*/
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
