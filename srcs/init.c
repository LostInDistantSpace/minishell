/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:07:47 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/18 15:29:27 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT) 
	{
		/*
		** might need child process specific things
		** C-\
		*/
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

t_env	*new_env(char *str)
{
	int		i;
	int		len;
	t_env	*var;

	if (!str)
		return (NULL);
	len = 0;
	var = malloc(sizeof(t_env));
	if (!var)
		return (NULL);
	var->next = NULL;
	while (str[len] && str[len] != '=')
		len++;
	var->key = malloc((len + 1) * sizeof(char));
	if (!var->key)
		return (free(var), NULL);
	var->key[len] = 0;
	i = -1;
	while (++i < len)
		var->key[i] = str[i];
	i++;
	var->value = ft_strdup(str + i);
	if (!var->value)
		return (free(var->key), free(var), NULL);
	return (var);
}

t_env	*add_env(t_env *head, t_env *var)
{
	t_env	*tmp;

	if (!var)
		return (head);
	if (!head)
	{
		head = var;
		return (head);
	}
	tmp = head;
	while (tmp->next)
			tmp = tmp->next;
	tmp->next = var;
	return (head);
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
		env = add_env(env, new_env(ep[i++]));
	return (env);
}
