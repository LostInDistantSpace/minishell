/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:07:47 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/10 18:59:58 by bmouhib          ###   ########.fr       */
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
void	init_sigaction(struct sigaction *sa)
{
	sa->sa_handler = sig_handler;
	sigemptyset(&sa->sa_mask);
	sigaddset(&sa->sa_mask, SIGTERM);
	sa->sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGINT, sa, NULL);
	sigaction(EOF, sa, NULL);
}

t_env	*add_env(t_env *env, char *str)
{
	int		i;
	int		len;
	t_env	*var;

	env = NULL;
	if (!str)
		return (NULL);
	len = 0;
	var = malloc(sizeof(t_env));
	while (str[len] && str[len] != '=')
		len++;
	var->key = malloc(len * sizeof(char));
	i = -1;
	while (++i < len)
		var->key[i] = str[i];
	len = i + 1;
	while (str[len])
		len++;
	var->value = malloc(len * sizeof(char));
	while (++i < len)
		var->value[i] = str[i];
	return (var);
}

t_env	*init(struct sigaction *sa, char **ep)
{
	int		i;
	t_env	*env;

	i = 0;
	init_sigaction(sa);
	if (!ep)
		return (NULL);
	env = NULL;
	while (ep[i])
		add_env(env, ep[i++]);
	return (env);
}
