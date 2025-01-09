/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:04:27 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/09 14:31:13 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//need exit

void	ft_echo(t_ast *node)
{
	int	i;

	if (!(ft_strcmp(node->args[1], "-n")))
	{
		i = 2;
		while (node->args[i])
		{
			ft_putstr_fd(node->args[i], STDOUT_FILENO);
			i++;
		}
	}
	else
	{
		i = 1;
		while (node->args[i])
		{
			ft_putstr_fd(node->args[i], STDOUT_FILENO);
			i++;
		}
		printf("\n");
	}
}

void	ft_pwd(void)
{
	char	*dir;

	dir = NULL;
	ft_putstr_fd(getcwd(dir, PATH_MAX), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	// protect?
}

void	ft_env(t_env **env)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (current->value != NULL)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void	ft_cd(t_ast *node, t_env **env)//not sure if this works
{
	t_env	*current;
	char	*old_pwd;

	current = *env;
	old_pwd = NULL;
	if (chdir(node->args[1]) == -1)
		return (perror(strerror(errno)));
	while (ft_strcmp(current->key, "OLD_PWD"))
		current = current->next;
	if (current->value)
		free(current->value);
	getcwd(old_pwd, PATH_MAX);
	current->value = ft_strdup(old_pwd);
	if (!current->value)
		return (perror(strerror(errno)));//replace with exit
}