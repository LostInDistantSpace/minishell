/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TESTS.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:19:09 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/07 23:52:38 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <math.h>

void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	print_type(t_token_type type)
{
	if (type == WORD)
		printf("WORD");
	else if (type == PIPE)
		printf("PIPE");
	else if (type == REDIR_IN)
		printf("REDIR_IN");
	else if (type == REDIR_OUT)
		printf("REDIR_OUT");
	else if (type == REDIR_APPEND)
		printf("REDIR_APPEND");
	else if (type == REDIR_HEREDOC)
		printf("REDIR_HEREDOC");
}

/*
Prints the tokens to verify the tokenization process.
*/
void	print_tokens(t_token *token)
{
	int		i;
	t_token	*ptr;

	ptr = token;
	printf("TOKENS : \n");
	printf("--------------------------------------------------\n");
	while (ptr)
	{
		i = 0;
		while (ptr->value[i])
			printf("Token: [%s] | ", ptr->value[i++]);
		printf("Type : ");
		print_type(ptr->type);
		printf("\n--------------------------------------------------\n");
		ptr = ptr->next;
	}
}

// Utility function to get the maximum depth of the tree
int	get_tree_depth(t_ast *node)
{
	int	left_depth;
	int	right_depth;

	if (!node)
		return (0);
	left_depth = get_tree_depth(node->left);
	right_depth = get_tree_depth(node->right);
	return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

// Recursive function to print the tree vertically
void	print_vertical_tree(t_ast *node, int level, int depth)
{
	int	i;

	if (!node)
		return ;
	print_vertical_tree(node->right, level + 1, depth);
	for (i = 0; i < level * 2; i++)
		printf("	");
	if (node->args && node->args[0])
		printf("%s\n", node->args[0]);
	else
		printf("type:%d\n", node->type);
	print_vertical_tree(node->left, level + 1, depth);
}

// Wrapper function to print the tree
void	print_ast_tree(t_ast *root)
{
	int	depth;

	if (!root)
	{
		printf("(empty tree)\n");
		return ;
	}
	depth = get_tree_depth(root);
	print_vertical_tree(root, 0, depth);
}
