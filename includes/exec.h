/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:22:40 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/03 15:38:31 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "minishell.h"
#include <stdbool.h>
#include <limits.h>
#include <sys/stat.h>

typedef struct s_data
{
	int			*exit_status;
	int			save_in;
	int			save_out;
	bool		is_child;
	bool		piped;
	t_ast		**ast;
	t_env		**env;
}	t_data;

void	ft_ast(t_ast *node, t_data *data);

void	exec(t_ast **head, t_env **start, int *e_status);
void	fork_pipe(t_ast *node, t_data *data);

void	ft_redirect(t_ast *node, t_data *data);
int		change_input(t_ast *node);
int		change_output(t_ast *node);
void	restore_in_out(t_data *data);

char	**get_env(t_env **env, t_data *data);

void	handle_commands(t_ast *node, t_data *data);
char	*get_path(char *cmd, t_data *data);
char	*check_command(char *command, t_data *data);

void	free_env(t_env **start);
void	free_data(t_data *data);
void	free_array(char ***array);
void	ft_error(t_data *data);

void	ft_echo(t_ast *node, t_data *data);
int		check_echo_flag(char *flag);
void	ft_pwd(t_data *data);
void	ft_env(t_ast *node, t_env **env, t_data *data);
void	ft_unset(t_ast *node, t_data *data);
void	ft_cd(t_ast *node, t_env **env, t_data *data);
void	go_home(t_env **env, t_data *data, char *old_pwd);
void	update_pwd(t_env **env);
void	update_old_pwd(t_env **env, char *old_pwd);
void	ft_exit(t_ast *node, t_data *data);
int		check_exit(char *arg);

void	ft_export(t_ast *node, t_data *data);
char	*get_key(char *var);
char	*get_value(char *var);
int		check_key_name(char *key, t_data *data);

unsigned int	ft_atoui(const char *nptr);

#endif