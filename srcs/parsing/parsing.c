/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:49:05 by bmouhib           #+#    #+#             */
/*   Updated: 2025/02/06 13:57:00 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(char *prompt)
{
	char	*line;

	line = readline(prompt);
	free(prompt);
	if (line && ft_strlen(line))
		add_history(line);
	return (line);
}

int	check_input(t_env **env, char *line, int *exit_status)
{
	if (g_signal == SIGINT)
	{
		*exit_status = 128 + g_signal;
		g_signal = 0;
		return (1);
	}
	if (!line)
	{
		free_env(env);
		write(STDOUT_FILENO, "exit\n", 5);
		exit(*exit_status);
	}
	return (0);
}

t_token	*parse(t_env **env, int *exit_status, char *home)
{
	int		syntax;
	char	*line;
	t_token	*token_list;

	token_list = NULL;
	line = get_input(prompt(*env, home));
	if (check_input(env, line, exit_status))
		return (NULL);
	syntax = syntax_checker(line);
	if (!syntax)
	{
		token_list = tokenize_input(line, *env, *exit_status);
		if (token_list && token_list->type < 0)
			return (token_list);
		handle_heredocs(&token_list, *env, exit_status);
		if (g_signal == SIGINT)
		{
			*exit_status = 128 + g_signal;
			g_signal = 0;
			return (free_tokens(&token_list), free(line), NULL);
		}
	}
	else if (syntax != 1)
		*exit_status = 2;
	return (free(line), token_list);
}
