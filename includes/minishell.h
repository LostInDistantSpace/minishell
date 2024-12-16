/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:58 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/16 22:45:59 by bmouhib          ###   ########.fr       */
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

/*typedef struct s_env
{
	char	**key;
	char	**value;
	// int		nb_value;
}	t_env;*/

extern int	g_signal;

char	*prompt(t_env *env);

t_env	*init(struct sigaction *sa, char **envp);

int		syntax_checker(char *line);
int		syntax_init(char **line, int *p, char *q, int *i);

t_token	*word_token(char **value, int num_word);
t_token	*tokenize_input(char *input);
t_ast	*parse_tokens(t_token *token);
t_token	*new_token(char *value, int type);
void	add_token(t_token **first, t_token *token);

void	print_tokens(t_token *token);

int		ft_strcmp(char *s1, char *s2);
int		word_num(char *input, int pos);
char	*ft_double_join(char *l, char *m, char *r);

char	*get_var(t_env *env, char *key);
char	*get_dir(t_env *env);

int		is_spe_char(char c);

void	free_array(char **array, int size);
void	free_token(t_token *token, int size);
void	free_env(t_env *env);
void	free_tokens(t_token *token);
void	free_all(t_env *env, t_token *token);

#endif
