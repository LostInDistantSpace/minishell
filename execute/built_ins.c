/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:26:07 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/11 13:26:55 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	echo(t_ast *node)
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
	exit(EXIT_SUCCESS);//maybe not, kills process
}

void	pwd(void)//idk if i need parameters
{
	char	*dir;
	size_t	size;

	dir = NULL;
	size = 0;
	printf("%s\n", getcwd(dir, size));
}
