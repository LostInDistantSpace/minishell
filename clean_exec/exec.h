/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:03:05 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/17 16:26:23 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "../includes/minishell.h"//not final

typedef struct s_data
{
	int			save_in;
	int			save_out;
	t_ast		**ast;
	t_env		**env;
}	t_data;

void	exec(t_ast **head, t_env **start);
void	ast(t_ast *node, t_data *data);

void	close_in_out(t_data *data);
void	restore_in_out(t_data *data);

#endif
