/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:29:22 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/23 13:33:19 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_key_name(char *key)
{
	int	i;

	i = 0;
	if (key[0] == '=')
		return (0);
	if (ft_isdigit(key[0]))
		return (0);
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
	if (key[0] == 0)
		printf("export : %s not a valid identifier\n", var);
	return (key);
}

int	check_echo_flag(char *flag)
{
	int	i;

	i = 1;
	if (flag[0] != '-')
		return (0);
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	go_home(t_env **env, t_data *data)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, "HOME") == 0)
		{
			if (chdir(current->value) == -1)
			{
				*data->exit_status = 1;
				return (perror(NULL));
			}
			*data->exit_status = 0;
			return;
		}
		current = current->next;
	}
	printf("cd : HOME not set\n");
	*data->exit_status = 1;
	return;
}