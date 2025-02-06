/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:52:05 by bmouhib           #+#    #+#             */
/*   Updated: 2025/02/06 15:37:30 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum)
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

int	rl_end_event(void)
{
	return (0);
}

void	sigquit_message(int signum)
{
	g_signal = signum;
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
	}
	else
		sa.sa_handler = sigquit_message;
	sigaction(SIGQUIT, &sa, NULL);
}

struct sigaction	init_sigaction(void)
{
	struct sigaction	sa;

	rl_event_hook = rl_end_event;
	sa.sa_handler = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGPIPE, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	return (sa);
}
