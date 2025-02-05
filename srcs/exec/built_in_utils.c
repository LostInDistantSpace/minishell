/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:29:22 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/05 14:39:21 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_exit(char *arg, t_data *data)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{	
			restore_in_out(data);
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

void	update_old_pwd(t_env **env, char *old_pwd)
{
	t_env	*current;

	current = *env;
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

void	go_home(t_env **env, t_data *data, char *old_pwd)
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
				return (perror("cd"));
			}
			update_old_pwd(env, old_pwd);
			update_pwd(env);
			*data->exit_status = 0;
			return ;
		}
		current = current->next;
	}
	print_error("cd", "HOME not set", data);
	*data->exit_status = 1;
	return ;
}
