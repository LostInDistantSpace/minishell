/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:00:40 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/16 23:06:49 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dir(t_env *env)
{
	int		home_len;
	char	*home;
	char	*cwd;
	char	*gwd;

	cwd = getcwd(NULL, 0);
	home = get_var(env, "HOME");
	if (!home)
		return (ft_strjoin(NON_PRINT BLUE BOLD END_NP, cwd));
	home_len = ft_strlen(home);
	if (home && !ft_strncmp(cwd, home, home_len))
	{
		gwd = ft_strjoin(NON_PRINT BLUE BOLD END_NP "~", cwd + home_len);
		free(cwd);
		return (gwd);
	}
	return (ft_strjoin(NON_PRINT BLUE BOLD END_NP, cwd));
}

char	*prompt(t_env *env)
{
	char	*tmp;
	char	*dir;
	char	*user;
	char	*prompt;

	if (get_var(env, "USER"))
		user = ft_strjoin(NON_PRINT GREEN BOLD END_NP, getenv("USER"));
	else
		user = NULL;
	dir = get_dir(env);
	if (user)
	{
		tmp = ft_double_join(user, " ", dir);
		prompt = ft_strjoin(tmp, NON_PRINT RESET_COLOR END_NP "$ ");
		free(tmp);
		free(user);
	}
	else
		prompt = ft_strjoin(dir, NON_PRINT RESET_COLOR END_NP "$ ");
	free(dir);
	return (prompt);
}
