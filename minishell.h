/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:58 by bmouhib           #+#    #+#             */
/*   Updated: 2024/11/25 19:54:34 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE
# include <unistd.h>
# include <signal.h>

# define BOLD "\e[1m"
# define RESET "\e[0m"

// Token type enumeration
typedef enum e_token_type
{
	TOKEN_WORD, // For commands and arguments
	TOKEN_PIPE, // For '|'
	TOKEN_REDIR_IN, // For '<'
	TOKEN_REDIR_OUT, // For '>'
	TOKEN_REDIR_APPEND, // For '>>'
	TOKEN_REDIR_HEREDOC, // For '<<'
	TOKEN_ENV_VAR, // For environment variables
}	t_token_type;

// Token structure
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_ast_node
{
	t_token_type		type;
	char				*args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

int	syntax_checker(void);

#endif