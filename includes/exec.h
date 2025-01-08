/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:22:40 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/08 15:07:25 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "minishell.h"
#include <errno.h>
#include <stdbool.h>

typedef struct s_data
{
	int			save_in;
	int			save_out;
	bool		is_child;
	t_ast		**ast;
	t_env		**env;
}	t_data;

void	ft_ast(t_ast *node, t_data *data);

void	exec(t_ast **head, t_env **start);
void	create_pipe(t_ast *node, t_data *data);

void	change_input(t_ast *node, t_data *data);
void	change_output(t_ast *node, t_data *data);

char	**get_env(t_env **env);

void	handle_commands(t_ast *node, t_data *data);
char	*get_path(char *cmd, char **env);

void	free_env(t_env **start);
void	free_ast(t_ast *node);
void	free_array(char **array);
void	restore_in_out(t_data *data);

void	ft_echo(t_ast *node);
void	ft_pwd();
void	ft_env(t_env **env);
void	ft_unset(t_ast *node, t_data *data);

void	ft_export(t_ast *node, t_data *data);
char	*get_key(char *var);
char	*get_value(char *var);
int		check_key_name(char *key);

#endif