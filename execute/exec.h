/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:38:11 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/10 15:16:05 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../includes/minishell.h"

typedef struct s_data
{
	int			save_in;
	int			save_out;
	t_ast		**ast;
	t_env	**env;
}	t_data;

void	env(t_ast *node);
void	echo(t_ast *node);

#endif
