/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:00:40 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/05 16:36:15 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dir(void)
{
	int		home_len;
	char	*home;
	char	*cwd;
	char	*gwd;

	home = getenv("HOME");
	home_len = ft_strlen(home);
	cwd = getcwd(NULL, 0);
	if (home && !ft_strncmp(cwd, home, home_len))
	{
		gwd = malloc(ft_strlen(cwd) - home_len + 2 * sizeof(char));
		gwd = ft_strjoin(BLUE BOLD "~", cwd + home_len);
		free(cwd);
		return (gwd);
	}
	return (ft_strjoin(BLUE BOLD, cwd));
}

char	*prompt(void)
{
	char	*tmp;
	char	*dir;
	char	*user;
	char	*prompt;

	if (getenv("USER"))
		user = ft_stroin(GREEN BOLD, getenv("USER"));
	else
		user = NULL;
	dir = get_dir();
	if (user)
	{
		tmp = ft_double_join(user, " ", dir);
		prompt = ft_strjoin(tmp, RESET_COLOR "$ ");
	}
	else
		prompt = ft_strjoin(dir, RESET_COLOR "$ ");
	return (free(tmp), free(dir), free(user), prompt);
}
