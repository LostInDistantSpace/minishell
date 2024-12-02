/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:58 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/02 14:34:10 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

# define BOLD "\e[1m"
# define RESET "\e[0m"

// Token type enumeration
typedef enum e_token_type
{
	TOKEN_WORD, // For commands and arguments
	// TOKEN_CMD,
	// TOKEN_ARG,
	// TOKEN_FILE,
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/*typedef struct s_env
{
	char	**key;
	char	**value;
	// int		nb_value;
}	t_env;*/

int	syntax_checker(void);

#endif