/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:23:01 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/20 14:44:16 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_export(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		printf("export %s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void	export(t_ast *node, t_data *data)
{
	if (node->args[1])
		print_export(data);

}