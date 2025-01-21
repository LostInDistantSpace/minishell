/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:07:47 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/21 22:31:41 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse	create_data(t_env *env, int exit_status)
{
	t_parse	data;

	data.env = env;
	data.exit_status = exit_status;
	return (data);
}

t_env	*init(struct sigaction *sa, char **ep, int *exit_status)
{
	int		i;
	t_env	*env;

	i = 0;
	*exit_status = 0;
	*sa = init_sigaction();
	if (!ep)
		return (NULL);
	env = NULL;
	while (ep[i])
		env = add_env(env, new_env(ep[i++]));
	if (!env) //idk if that's right
	{
		env = add_env(env, new_env(ft_strjoin("PWD=", getcwd(NULL, 0))));
		env = add_env(env, empty_env("OLDPWD"));
		env = add_env(env, new_env("SHLVL=1"));
	}
	return (env);
}
