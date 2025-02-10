/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:23:24 by bmouhib           #+#    #+#             */
/*   Updated: 2025/02/10 19:40:52 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*new_node(t_token *token)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	node->args = token->value;
	node->type = token->type;
	token->value = NULL;
	return (node);
}

void	place_word(t_ast **head, t_ast *node)
{
	t_ast	*ptr;

	ptr = *head;
	if (!ptr)
		*head = node;
	else if (ptr->type == PIPE)
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

void	place_redir(t_ast **head, t_ast *node)
{
	t_ast	*ptr;

	ptr = *head;
	if (!ptr)
		*head = node;
	else
	{
		while (ptr->right)
			ptr = ptr->right;
		ptr->right = node;
	}
}

void	place_pipe(t_ast **head, t_ast *node)
{
	t_ast	*tmp;
	t_ast	*ptr;

	ptr = *head;
	if (!ptr)
		*head = node;
	else if (ptr->type == PIPE)
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
	t_token	*next;

	head = NULL;
	while (token)
	{
		node = new_node(token);
		if (!node)
			return (free_ast(&head), new_node(new_token(NULL, -1, 0)));
		next = token->next;
		free(token);
		if (node->type == PIPE)
			place_pipe(&head, node);
		if (node->type >= REDIR_IN && node->type <= APPEND)
			place_redir(&head, node);
		if (node->type == WORD)
			place_word(&head, node);
		token = next;
	}
	return (head);
}
