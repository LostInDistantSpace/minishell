/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:18:59 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/28 15:30:19 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	count_size(t_env **start)
{
	t_env	*current;
	int		size;

	current = (*start);
	size = 0;
	while (current != NULL)
	{
		current = current->next;
		size++;
	}
	return (size);
}

char	*join_env(t_env *var, t_data *data)
{
	char	*join;
	char	*big_join;

	join = ft_strjoin(var->key, "=");
	if (!join)
		return (ft_error(data), NULL);
	big_join = ft_strjoin(join, var->value);
	free(join);
	if (!big_join)
		return (ft_error(data), NULL);
	return (big_join);
}

char	**get_env(t_env **env, t_data *data)
{
	char	**new_env;
	int		i;
	t_env	*current;

	new_env = malloc(sizeof(char *) * (count_size(env) + 1));
	if (!new_env)
		return (ft_error(data), NULL);
	i = 0;
	current = *env;
	while (current)
	{
		new_env[i] = join_env(current, data);
		i++;
		current = current->next;
	}
	new_env[i] = 0;
	return (new_env);
}
