/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:07:47 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/19 16:28:37 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init(struct sigaction *sa, char **ep)
{
	int		i;
	t_env	*env;

	i = 0;
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
		env = add_env(env, new_env("SHLVL=0"));
		env = add_env(env, empty_env("_")); //to do
	}
	return (env);
}
