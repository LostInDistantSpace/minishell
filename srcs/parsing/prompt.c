/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:00:40 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/21 15:42:19 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home(char *home)
{
	int		home_len;
	char	*cwd;
	char	*gwd;

	cwd = getcwd(NULL, 0);
	if (!home || !cwd)
		return (ft_strjoin(NON_PRINT B_BLUE BOLD END_NP, cwd));
	home_len = ft_strlen(home);
	if (home && !ft_strncmp(cwd, home, home_len))
	{
		gwd = ft_strjoin(NON_PRINT B_BLUE BOLD END_NP "~", cwd + home_len);
		free(cwd);
		return (gwd);
	}
	return (ft_strjoin(NON_PRINT B_BLUE BOLD END_NP, cwd));
}

char	*prompt(t_env *env, char *home)
{
	char	*tmp;
	char	*dir;
	char	*user;
	char	*prompt;

	user = get_var(env, "USER");
	if (user)
	{
		tmp = user;
		user = ft_strjoin(NON_PRINT GREEN BOLD END_NP, tmp);
		free(tmp);
	}
	dir = get_home(home);
	if (user)
	{
		tmp = ft_double_join(user, " ", dir);
		prompt = ft_strjoin(tmp, NON_PRINT RESET_COLOR END_NP "$ ");
		free(tmp);
		free(user);
	}
	else
		prompt = ft_strjoin(dir, NON_PRINT RESET_COLOR END_NP "$ ");
	return (free(home), free(dir), prompt);
}
