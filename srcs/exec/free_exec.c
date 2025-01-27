/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:01:13 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/27 14:26:25 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_error(t_data *data)
{
	free_env(data->env);
	free_ast(data->ast);
	free(data);
	printf("Error\n");
	exit(EXIT_FAILURE);
}

void	free_data(t_data *data)
{
	free_env(data->env);
	free_ast(data->ast);
	free(data);
}
