/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:00:40 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/04 23:00:54 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(void)
{
	char	*dir;
	char	*tmp;
	char	*prompt;

	dir = get_dir();
	prompt = ft_double_join(GREEN, BOLD, getenv("USER"));
	tmp = ft_double_join(prompt, "@", getenv("NAME"));
	free(prompt);
	prompt = ft_double_join(tmp, " ", BLUE);
	free(tmp);
	tmp = ft_double_join(prompt, dir, "$ ");
	prompt = ft_strjoin(tmp, RESET_COLOR);
	return (free(tmp), free(dir), prompt);
}
