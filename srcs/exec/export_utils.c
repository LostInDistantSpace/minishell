/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:29:22 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/16 17:13:22 by lemarian         ###   ########.fr       */
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
			return (&var[i]);
		i++;
	}
	return (&var[i]);
}

char	*get_key(char *var)
{
	int		i;
	char	*key;

	i = 0;
	key = NULL;
	while (var[i] && var[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		key[i] = var[i];
		i++;
	}
	key[i] = 0;
	return (key);
}
