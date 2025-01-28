/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:29:22 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/28 14:47:09 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_exit(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{	
			printf("exit : %s : numeric argument required\n", arg);
			return (0);
		}
		i++;
	}
	return (1);
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

void	update_old_pwd(char *old_pwd, t_env **env)
{
	t_env	*current;

	current = *env;
	if (!old_pwd)
		return ;
	while (current)
	{
		if (ft_strcmp(current->key, "OLDPWD") == 0)
		{
			if (current->value)
				free(current->value);
			current->value = old_pwd;
		}
		current = current->next;
	}
}

void	update_pwd(t_env **env)
{
	t_env	*current;
	char	*buff;

	current = *env;
	buff = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, "PWD") == 0)
		{
			if (current->value)
				free(current->value);
			current->value = getcwd(buff, PATH_MAX);
			free(buff);
		}
		current = current->next;
	}
}

void	go_home(t_env **env, t_data *data)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, "HOME") == 0)
		{
			if (!current->value || current->value[0] == 0)
				return ;
			if (chdir(current->value) == -1)
			{
				*data->exit_status = 1;
				return (perror(NULL));
			}
			*data->exit_status = 0;
			return ;
		}
		current = current->next;
	}
	printf("cd : HOME not set\n");
	*data->exit_status = 1;
	return ;
}
