/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:43:00 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/05 15:10:27 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

int	check_key_name(char *key, t_data *data)
{
	int	i;

	i = 0;
	if (key[0] == '=' || ft_isdigit(key[0]))
	{	
		restore_in_out(data);
		printf("export: '%s': not a valid identifier\n", key);
		*data->exit_status = 1;
		free(key);
		return (0);
	}
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{	
			restore_in_out(data);
			printf("export: '%s': not a valid identifier\n", key);
			*data->exit_status = 1;
			free(key);
			return (0);
		}
		i++;
	}
	return (1);
}

char	*get_key(char *var, t_data *data)
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
	if (key[0] == 0)
	{	
		restore_in_out(data);
		printf("export : '%s' not a valid identifier\n", var);
	}
	return (key);
}
