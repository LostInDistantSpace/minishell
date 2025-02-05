/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:00:40 by bmouhib           #+#    #+#             */
/*   Updated: 2025/02/05 17:53:54 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home(char *home)
{
	int		home_len;
	char	*cwd;
	char	*gwd;

	gwd = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	home_len = ft_strlen(home);
	if (home && !ft_strncmp(cwd, home, home_len))
		gwd = ft_strjoin(NON_PRINT B_MAGENTA BOLD END_NP "~", cwd + home_len);
	else
		gwd = ft_strjoin(NON_PRINT B_MAGENTA BOLD END_NP, cwd);
	return (free(cwd), gwd);
}

char	*prompt(t_env *env, char *home)
{
	char	*tmp;
	char	*dir;
	char	*user;
	char	*prompt;

	dir = get_home(home);
	user = get_var(env, "USER");
	if (user)
	{
		tmp = user;
		user = ft_strjoin(NON_PRINT B_GREEN BOLD END_NP, tmp);
		free(tmp);
		tmp = ft_double_join(user, " ", dir);
		free(user);
		prompt = ft_strjoin(tmp, NON_PRINT RESET_COLOR END_NP "$ ");
		free(tmp);
	}
	else
		prompt = ft_strjoin(dir, NON_PRINT RESET_COLOR END_NP "$ ");
	if (dir)
		free(dir);
	if (home)
		free(home);
	return (prompt);
}
