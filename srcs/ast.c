/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:23:24 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/18 17:23:41 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*new_node(void)
{
	t_ast	*node;

	node = malloc(sizeof(node));
	node->left = NULL;
	node->right = NULL;
	node->args = NULL;
	node->type = WORD;
	return (node);
}

/*
Iterates through the tokens, 
building an abstract syntax tree (AST) 
that represents the input string.
*/
t_ast	*parse_tokens(t_token *token)
{
	while (token->next)
	{
		// heredoc_reader();
		// transom token into node -> expand variables as needed, remove quotes
		token = token->next;
	}
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
