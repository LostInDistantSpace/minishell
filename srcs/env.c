/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:05:21 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/04 22:05:41 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*get_dir(void)
{
	int		home_len;
	char	*home;
	char	*cwd;
	char	*gwd;

	home = getenv("HOME");
	home_len = ft_strlen(home);
	cwd = getcwd(NULL, 0);
	if (!ft_strncmp(cwd, home, home_len))
	{
		gwd = malloc(ft_strlen(cwd) - home_len + 2 * sizeof(char));
		gwd = ft_strjoin("~", cwd + home_len);
		free(cwd);
		return (ft_double_join(BOLD, gwd, RESET_COLOR));
	}
	return (ft_double_join(BOLD, cwd, RESET_COLOR));
}
