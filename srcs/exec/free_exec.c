/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:01:13 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/05 15:25:29 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*exit_command(t_data *data)
{
	if (data->is_child)
		exit_child(data);
	return (NULL);
}

void	print_error(char *src, char *error, t_data *data)
{
	restore_in_out(data);
	printf("%s : %s\n", src, error);
}

void	ft_error(t_data *data)
{
	restore_in_out(data);
	free_env(data->env);
	free_ast(data->ast);
	free(data);
	printf("Minishell : %s", strerror(errno));
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

	if (data->is_child == false)
		return ;
	status = *data->exit_status;
	close(data->save_in);
	close(data->save_out);
	free_data(data);
	exit(status);
}
