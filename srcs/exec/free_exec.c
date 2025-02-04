/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:01:13 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/04 17:32:59 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_error(t_data *data)
{
	free_env(data->env);
	free_ast(data->ast);
	free(data);
	printf("Minishell : \n");
	perror(NULL);
	exit(EXIT_FAILURE);
}

void	free_data(t_data *data)
{
	free_env(data->env);
	free_ast(data->ast);
	free(data);
}

void	exit_child(t_data *data)
{
	int	status;

	status = *data->exit_status;
	close(data->save_in);
	close(data->save_out);
	free_data(data);
	exit(status);
}
