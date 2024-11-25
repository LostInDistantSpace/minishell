/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:25 by bmouhib           #+#    #+#             */
/*   Updated: 2024/11/25 19:44:28 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_prompt(char *current_dir)
{
	if (current_dir)
	{
		printf(BOLD "%s >" RESET, current_dir);
	}
}

int	main(int argc, char **argv)
{
	int					end_signal;
	char				*current_dir;
	struct sigaction	sa;

	end_signal = 0;
	if (argc != 1)
		return (1);
	signal_handling(&sa);
	while (!end_signal)
	{
		ft_prompt(current_dir);
		syntax_checker();
		tokenize();
		do_stuff();
	}
	return (0);
}
