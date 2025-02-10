/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:52:05 by bmouhib           #+#    #+#             */
/*   Updated: 2025/02/10 17:41:19 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rl_end_event(void)
{
	return (0);
}

void	parsing_sig_handler(int signum)
{
	g_signal = signum;
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_done = 1;
	}
}

void	exec_sig_handler(int signum)
{
	g_signal = signum;
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_done = 1;
	}
}

void	sigquit_manager(int status)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (!status)
	{
		if (g_signal == SIGQUIT)
			printf("Quit (core dumped)\n");
		g_signal = 0;
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
		sa.sa_handler = parsing_sig_handler;
	}
	else
	{
		sa.sa_handler = exec_sig_handler;
		sigaction(SIGQUIT, &sa, NULL);
	}
	sigaction(SIGINT, &sa, NULL);
}

struct sigaction	init_sigaction(void)
{
	struct sigaction	sa;

	rl_event_hook = rl_end_event;
	sa.sa_handler = parsing_sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
	return (sa);
}
