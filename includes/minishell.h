/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:58 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/10 00:14:50 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE
# include "colors.h"
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
	REDIR_APPEND, // For '>>'
	REDIR_HEREDOC, // For '<<'
}	t_token_type;

// Token structure
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_ast
{
	t_token_type	type;
	char			*args;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

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

extern int	g_signal;

char				*prompt(void);

// struct sigaction	sa_init(void);
void				sa_init(struct sigaction *sa);

int					syntax_checker(char *line);
int					syntax_init(char **line, int *p, char *q, int *i);

t_token				*tokenize_input(char *input);
t_ast				*parse_tokens(t_token *token);
void				print_tokens(t_token *token);

int					ft_strcmp(char *s1, char *s2);
char				*ft_double_join(char *l, char *m, char *r);

char				*get_var(t_env *env, char *key);
char				*get_dir(void);

int					is_special_char(char c);

#endif