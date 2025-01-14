/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:01:13 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/14 15:44:46 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_data(t_data *data)
{
	free_env(data->env);
	free_ast(data->ast);
	free(data);
}

void	ft_error(t_data *data)
{
	free_data(data);
	exit(EXIT_FAILURE);
}