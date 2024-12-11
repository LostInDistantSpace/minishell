/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:27:53 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/11 13:33:03 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	count_size(t_env **start)
{
	t_env	*current;
	int	size;

	current = (*start);
	size = 0;
	while (current != NULL)
	{
		current = current->next;
		size++;
	}
	return(size);
}

char	**get_env(t_data *data)
{
	char	**env;
	int		size;

	size = count_size(data->env);
	env = malloc(sizeof(char*) * size);
	if (!env)
		return (NULL);
	return (env);
}
