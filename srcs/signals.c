/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:07:47 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/09 23:10:51 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = SIGINT;
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	g_signal = 0;
}

void	sa_init(struct sigaction *sa)
{
	sa->sa_handler = sig_handler;
	sigemptyset(&sa->sa_mask);
	sigaddset(&sa->sa_mask, SIGTERM);
	sa->sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGINT, sa, NULL);
	sigaction(EOF, sa, NULL);
}

/*struct sigaction	sa_init(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGTERM);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	sigaction(EOF, &sa, NULL);
	return (sa);
}*/
