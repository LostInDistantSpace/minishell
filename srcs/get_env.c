/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:18:59 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/06 17:29:16 by lemarian         ###   ########.fr       */
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
	int		i;
	t_env	*current;
	char	*join;
	char	*var;

	env = malloc(sizeof(char*) * count_size(data->env) + 1);
	if (!env)
		return (NULL);//replace with exit function
	i = 0;
	current = data->env;
	while (current)
	{
		join = ft_strjoin(current->key, "=");
		var = ft_strjoin(join, current->value);
		env[i] = ft_strdup(var);
		if (!join || !var || !env[i])
			return (free(join), free(var), free(env[i]), NULL);
		free(join);
		free(var);
		i++;
		current = current->next;
	}
	env[i] = '\0';
	return (env);
}