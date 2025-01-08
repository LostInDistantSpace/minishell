/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:04:27 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/08 14:17:39 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//need cd and exit

void	echo(t_ast *node, t_data *data)
{
	int	i;

	if (!(ft_strncmp(node->args[1], "-n", 2)))
	{
		i = 2;
		while (node->args[i])
		{
			printf("%s", node->args[i]);
			i++;
		}
	}
	else
	{
		i = 1;
		while (node->args[i])
		{
			printf("%s", node->args[i]);
			i++;
		}
		printf("\n");
	}
}

void	pwd(t_data *data)
{
	char	*dir;
	size_t	size;

	dir = NULL;
	size = 0;
	printf("%s\n", getcwd(dir, size));
}

void	env(t_ast *node, t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (current->value != NULL)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}