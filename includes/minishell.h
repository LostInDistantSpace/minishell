/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:58 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/17 19:43:05 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE
# include "colors.h"
# include "parsing.h"
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

// Token type enumeration
typedef enum e_token_type
{
	WORD, // For commands and arguments
	PIPE, // For '|'
	REDIR_IN, // For '<'
	REDIR_OUT, // For '>'
	REDIR_HEREDOC, // For '<<'
	REDIR_APPEND, // For '>>'
}	t_token_type;

// Token structure
typedef struct s_token
{
	t_token_type	type;
	char			**value;
	struct s_token	*next;
}	t_token;

typedef struct s_ast
{
	t_token_type	type;
	char			**args;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

extern int	g_signal;

char	*prompt(t_env *env);

t_env	*init(struct sigaction *sa, char **envp);

void	free_array(char **array, int size);
void	free_token(t_token *token, int size);
void	free_env(t_env *env);
void	free_tokens(t_token *token);

#endif
