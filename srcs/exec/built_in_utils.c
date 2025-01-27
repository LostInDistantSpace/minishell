/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:29:22 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/27 14:47:20 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

void	update_pwd(t_env **env, t_data *data)
{
	t_env	*traverse_1;
	t_env	*traverse_2;
	char	*buff;

	traverse_1 = *env;
	traverse_2 = *env;
	buff = NULL;
	while (ft_strcmp(traverse_1->key, "OLDPWD"))
		traverse_1 = traverse_1->next;
	if (traverse_1->value)
		free(traverse_1->value);
	while (ft_strcmp(traverse_2->key, "PWD"))
		traverse_2 = traverse_2->next;
	traverse_1->value = ft_strdup(traverse_2->value);
	if (!traverse_1->value)
		ft_error(data);
	free(traverse_2->value);
	traverse_2->value = getcwd(buff, PATH_MAX);
	free(buff);
	*data->exit_status = 0;
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
			return ;
		}
		current = current->next;
	}
	printf("cd : HOME not set\n");
	*data->exit_status = 1;
	return ;
}
