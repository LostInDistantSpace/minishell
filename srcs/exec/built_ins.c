/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:04:27 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/03 14:34:40 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_exit(t_ast *node, t_data *data)
{
	int	final_exit;

	if (data->is_child == true || data->piped == true)
		return ;
	if (!node->args[1] || !check_exit(node->args[1]))
		final_exit = *data->exit_status;
	else if (node->args[2] != NULL)
	{
		printf("exit : too many arguments\n");
		*data->exit_status = 1;
		return ;
	}
	else
	{
		if (node->args[1][0] == '-')
			final_exit = 255;
		else if (ft_atoui(node->args[1]) > 255)
			final_exit = 42;
		else
			final_exit = ft_atoui(node->args[1]);
	}
	restore_in_out(data);
	free_data(data);
	exit(final_exit);
}

void	ft_echo(t_ast *node, t_data *data)
{
	int	i;
	int	line;

	i = 1;
	line = 0;
	if (node->args[1] != NULL)
	{
		if (ft_strncmp(node->args[1], "-n", 2) == 0)
		{
			line = 1;
			while (node->args[i] && check_echo_flag(node->args[i]))
				i++;
		}
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

void	ft_env(t_ast *node, t_env **env, t_data *data)
{
	t_env	*current;

	if (node->args[1] != NULL)
	{	
		*data->exit_status = 1;
		return ;
	}
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
	char	*old_pwd;

	old_pwd = NULL;
	if (!node->args[1] || ft_strcmp(node->args[1], "~") == 0)//update pwd??
		return (go_home(env, data));
	if (node->args[2])
	{
		printf("cd : too may arguments\n");//exit status??
		return ;
	}
	old_pwd = getcwd(old_pwd, PATH_MAX);
	if (!old_pwd)
		perror(NULL);
	if (chdir(node->args[1]) == -1)
	{	
		*data->exit_status = 1;
		return (perror(NULL));
	}
	update_old_pwd(old_pwd, env);
	update_pwd(env);
	*data->exit_status = 0;
}
