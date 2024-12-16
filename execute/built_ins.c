/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:26:07 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/16 14:00:26 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

void	env(t_data *data)
{
	char **env;
	int	i;

	env = get_env(data);
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	free_array(env);
}
