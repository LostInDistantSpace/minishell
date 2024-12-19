/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:23:24 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/19 19:42:31 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*new_node(t_token *token)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	node->left = NULL;
	node->right = NULL;
	node->args = token->value; //deep copy OR put token->value to NULL
	node->type = token->type;
	return (node);
}

void	place_word(t_ast *head, t_ast *node)
{
	t_ast	*ptr;

	ptr = head;
	if (ptr->type == PIPE)
	{
		while (ptr->right && ptr->right->type == PIPE)
			ptr = ptr->right;
		if (ptr->right)
		{
			ptr = ptr->right;
			ptr->left = node;
		}
		else
			ptr->right = node;
	}
	else
		ptr->left = node;
}

void	place_redir(t_ast *head, t_ast *node)
{
	t_ast	*ptr;

	ptr = head;
	while (ptr->right)
		ptr = ptr->right;
	ptr->right = node;
}

void	place_pipe(t_ast **head, t_ast *node)
{
	t_ast	*tmp;
	t_ast	*ptr;

	ptr = *head;
	if (ptr->type == PIPE)
	{
		while (ptr->right && ptr->right->type == PIPE)
			ptr = ptr->right;
		if (!ptr->right)
			ptr->right = node;
		else
		{
			tmp = ptr->right;
			ptr->right = node;
			ptr = ptr->right;
			ptr->left = tmp;
		}
	}
	else
	{
		*head = node;
		(*head)->left = ptr;
	}
}

/*
Iterates through the tokens, 
building an abstract syntax tree (AST) 
that represents the input string.
*/
t_ast	*parse_tokens(t_token *token)
{
	t_ast	*head;
	t_ast	*node;

	head = NULL;
	while (token)
	{
		node = new_node(token);
		if (!head)
			head = node;
		else
		{
			if (node->type == PIPE)
				place_pipe(&head, node);
			if (node->type >= REDIR_IN && node->type <= REDIR_APPEND)
				place_redir(head, node);
			if (node->type == WORD)
				place_word(head, node);
		}
		token = token->next;
	}
	return (head);
}
