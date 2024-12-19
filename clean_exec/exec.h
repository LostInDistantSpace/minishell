/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:03:05 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/19 15:52:25 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "../includes/minishell.h"//not final
#include <errno.h>
#include <stdbool.h>

typedef struct s_data
{
	int			save_in;
	int			save_out;
	bool		pipe;
	t_ast		**ast;
	t_env		**env;
}	t_data;

void	exec(t_ast **head, t_env **start);
void	ast(t_ast *node, t_data *data);

void	close_in_out(t_data *data);
void	restore_in_out(t_data *data);
void	change_input(t_ast *node, t_data *data);
void	change_output(t_ast *node, t_data *data);

void	create_pipe(t_ast *node, t_data *data);

void	handle_commands(t_ast *node, t_data *data);
char	*get_path(char *cmd, char **ep);

void	free_array(char **array);

#endif
