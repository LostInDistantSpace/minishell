/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:38:11 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/11 18:09:05 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../includes/minishell.h"
# include <stdbool.h>

typedef struct s_data
{
	int			save_in;
	int			save_out;
	bool		child;
	t_ast		**ast;
	t_env	**env;
}	t_data;

void	env(t_ast *node);
void	echo(t_ast *node);

void	ast(t_ast *node, t_data *data);

void	change_input(t_ast *node, t_data *data);
void	change_output(t_ast *node, t_data *data);

void	find_command(t_ast *node, t_data *data);
char	*get_path(char *cmd, char **ep);
char	**get_env(t_data *data);

#endif
