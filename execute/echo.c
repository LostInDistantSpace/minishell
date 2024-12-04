/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:28:58 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/04 14:48:36 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	echo(t_ast_node *node)
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
	exit(EXIT_SUCCESS);
}
