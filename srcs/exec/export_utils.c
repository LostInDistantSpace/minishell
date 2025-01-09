/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:29:22 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/08 14:51:31 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_key_name(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*get_value(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (&var[i + 1]);
		i++;
	}
	return (NULL);
}

char	*get_key(char *var)
{
	int	i;
	char	*key;

	i = 0;
	key = NULL;
	while (var[i] && var[i] != '=')
	{
		key[i] = var[i];
		i++;
	}
	return (key);
}