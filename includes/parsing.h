/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:12:55 by bmouhib           #+#    #+#             */
/*   Updated: 2025/02/05 15:41:19 by bmouhib          ###   ########.fr       */
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

typedef struct s_parse_data
{
	t_env	*env;
	int		exit_status;
}	t_parse;

t_token	*parse(t_env **env, int *exit_status, char *home);

int		syntax_checker(char *line);
int		syntax_init(char *line, char *q, int *i);
int		is_forbiddenchar(char c);

t_token	*word_token(char ***value, int num_word);
t_token	*tokenize_input(char *input, t_env *env, int exit_status);
t_ast	*parse_tokens(t_token *token);
t_token	*new_token(char *value, int type);
void	add_token(t_token **first, t_token *token);
int		seek_spe_char(char *input, int pos);
int		handle_words(char *input, int *pos, t_token **head, t_parse p);

int		ft_strcmp(char *s1, char *s2);
char	*ft_double_join(char *l, char *m, char *r);

char	*get_var(t_env *env, char *key);

int		is_quotes(char c);
int		is_spechar(char c);
char	*substr_del(char *s, unsigned int start, size_t len);

t_sigac	init_sigaction(void);
void	sigquit_manager(int status);

t_env	*new_env(char *str);
t_env	*empty_env(char *str);
t_env	*add_env(t_env *head, t_env *var);

void	handle_heredocs(t_token **token, t_env *env, int *exit_status);

void	init_expand(char **result, char *quote, int *step, int *i);
char	*special_var(char var, char *previous, int exit_status);
char	*expand(char *str, t_env *env, char q, int exit_status);
char	*get_var_from_key(t_env *env, char *raw, int *i);
char	*concat_var(t_env *env, char **array, int *i, int exit_status);
char	*fill_from_step(char *prev, char *str, int start, int stop);

int		char_not_handled(char c);
int		unclosed_quote(void);
int		unexpected_token(char *token);

#endif