/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:00:40 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/28 15:22:44 by lemarian         ###   ########.fr       */
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
		return (free(cwd), NULL);
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

	user = get_var(env, "USER");
	if (user)
	{
		tmp = user;
		user = ft_strjoin(NON_PRINT B_GREEN BOLD END_NP, tmp);
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
