/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:38:11 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/09 13:54:11 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../includes/minishell.h"

typedef struct s_data
{
	int			save_in;
	int			save_out;
	t_env		**ast;
	t_ast_node	**env;
}	t_data;

void	env(t_ast_node *node);
void	echo(t_ast_node *node);

#endif
