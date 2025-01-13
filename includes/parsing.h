/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:12:55 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/09 21:50:33 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <dirent.h>

typedef enum e_token_type	t_token_type;
typedef struct s_token		t_token;
typedef struct s_ast		t_ast;
typedef struct s_env		t_env;
typedef struct sigaction	t_sigac;

t_token	*parse(t_env *env);

int		syntax_checker(char *line);
int		syntax_init(char **line, char *q, int *i);
int		is_forbiddenchar(char c);

t_token	*word_token(char **value, int num_word);
t_token	*tokenize_input(char *input);
t_ast	*parse_tokens(t_token *token);
t_token	*new_token(char *value, int type);
void	add_token(t_token **first, t_token *token);

int		ft_strcmp(char *s1, char *s2);
int		word_num(char *input, int pos);
char	*ft_double_join(char *l, char *m, char *r);

char	*get_var(t_env *env, char *key);
char	*get_dir(t_env *env);

int		is_spechar(char c);

void	sig_handler(int signum);
t_sigac	init_sigaction(void);

t_env	*new_env(char *str);
t_env	*empty_env(char *str);
t_env	*add_env(t_env *head, t_env *var);

void	handle_heredocs(t_token *token, t_env *env);
char	*heredoc_expand(char *str, t_env *env);

void	init_expand(char **result, char *quote, int *step, int *i);
char	*copy_key(char *str, int *i);
char	*concat_var(t_env *env, char *previous, char *raw, int *i);
char	*fill_from_step(char *prev, char *str, int start, int stop);
char	*expand(char *str, t_env *env, char q);
void	clean_tokens(t_token *tok, t_env *env);

/******************/
/* TESTS FUNCTIONS*/
/******************/
void	print_env(t_env *env);
void	print_type(t_token_type type);
void	print_tokens(t_token *token);
void	print_ast_tree(t_ast *ast);

#endif