/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:25 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/02 14:50:03 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 - *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	*cur_dir(char *current_dir, char *base_dir)
{
	(void)base_dir;
	if (ft_strcmp(current_dir, base_dir))
		return (BOLD "~$ " RESET);
	return ("~$ ");
}

int	main(int argc, char **argv)
{
	int					end_signal;
	char				*line;
	char				*current_dir;
	t_env				*env;
	struct sigaction	sa;

	(void)argv;
	if (argc != 1)
		return (1);
	signal_handling(&sa);
	get_env(env);
	end_signal = 0;
	while (!end_signal)
	{
		line = readline(cur_dir("~", "/home/user"));
		printf("%s\n", line);
		if (!line)
			end_signal = 1;
		syntax_checker();
		tokenize();
		do_stuff();
		free(line);
	}
	return (0);
}
