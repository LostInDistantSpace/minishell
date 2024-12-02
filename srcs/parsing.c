/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:49:05 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/02 19:21:18 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*new_node(void)
{
	t_ast_node	*node;

	node = malloc(sizeof(node));
	node->left = NULL;
	node->right = NULL;
	node->args = NULL;
	node->type = TOKEN_WORD;
	return (node);
}

/*
Iterates through the tokens, 
building an abstract syntax tree (AST) 
that represents the input string.
*/
t_ast_node	*parse_tokens(t_token *token)
{
	while (token->next)
		token = token->next;
	return (new_node());
}

/*
Parses a command and its arguments, 
creating a command node in the AST.
*/
void	parse_command(char *cmd)
{
	(void)cmd;
}

/*
Parses pipeline tokens, 
creating pipeline nodes in the AST.
*/
void	parse_pipeline(void)
{
}

/*
Parses redirection tokens, 
creating redirection nodes in the AST.
*/
void	parse_redirection(char *redir)
{
	(void)redir;
}

/*
Creates a file node for redirections in the AST.
*/
// void	create_file_node(char *file)
// {
// }
