/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:04:27 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/20 15:12:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_exit(t_ast *node, t_data *data)
{
	int	final_exit;

	if (data->is_child == true || data->piped == true)
		return ;
	if (!node->args[1])
		final_exit = *data->exit_status;
	else
	{
		if (node->args[1][0] == '-')
			final_exit = 255;
		else if (ft_atoui(node->args[1]) > 255)
			final_exit = 42;
		else
			final_exit = ft_atoui(node->args[1]);
	}
	free_ast(data->ast);
	free_env(data->env);
	restore_in_out(data);
	free(data);
	exit(final_exit);
}

void	ft_echo(t_ast *node, t_data *data)
{
	int	i;
	int	line;

	i = 1;
	line = 0;
	if (ft_strcmp(node->args[i], "-n") == 0)
	{
		line = 1;
		while (ft_strcmp(node->args[i], "-n") == 0)
			i++;
	}
	while (node->args[i])
	{
		ft_putstr_fd(node->args[i], STDOUT_FILENO);
		if (node->args[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (line == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	*data->exit_status = 0;
}

void	ft_pwd(t_data *data)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, PATH_MAX);
	if (!dir)
	{
		perror(NULL);
		*data->exit_status = 1;
	}
	else
	{
		ft_putstr_fd(dir, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		*data->exit_status = 0;
		free(dir);
	}
}

void	ft_env(t_env **env, t_data *data)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (current->value != NULL)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	*data->exit_status = 0;
}

void	ft_cd(t_ast *node, t_env **env, t_data *data)
{
	t_env	*current;
	char	*buff;
	char	*old_pwd;

	current = *env;
	buff = NULL;
	old_pwd = getcwd(buff, PATH_MAX);
	free(buff);
	if (!old_pwd)
		return (perror(NULL));
	if (chdir(node->args[1]) == -1)
	{	
		*data->exit_status = 1;
		free(old_pwd);
		return (perror(NULL));
	}
	while (ft_strcmp(current->key, "OLDPWD"))
		current = current->next;
	if (current->value)
		free(current->value);
	current->value = old_pwd;
}
