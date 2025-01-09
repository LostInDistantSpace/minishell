/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:18:59 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/09 15:02:17 by lemarian         ###   ########.fr       */
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

char	**get_env(t_env **env)
{
	char	**new_env;
	int		i;
	t_env	*current;
	char	*join;
	char	*var;

	new_env = malloc(sizeof(char*) * (count_size(env) + 1));
	if (!new_env)
		return (NULL);//replace with exit function
	i = 0;
	current = *env;
	while (current)
	{
		join = ft_strjoin(current->key, "=");
		var = ft_strjoin(join, current->value);
		new_env[i] = ft_strdup(var);
		if (!join || !var || !new_env[i])
			return (free(join), free(var), free(new_env[i]), NULL);
		free(join);
		free(var);
		i++;
		current = current->next;
	}
	new_env[i] = 0;
	return (new_env);
}