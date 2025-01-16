/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:49:05 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/14 17:13:07 by bmouhib          ###   ########.fr       */
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

int	check_input(t_env **env, char *line)
{
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		return (1);
	}
	if (!line)
	{
		free_env(env);
		exit(write(STDOUT_FILENO, "exit\n", 5));
		// need exit function
	}
	return (0);
}

t_token	*parse(t_env *env, int exit_status)
{
	int		syntax;
	char	*line;
	t_token	*token_list;

	token_list = NULL;
	line = get_input(prompt(env));
	if (check_input(&env, line))
		return (NULL);
	syntax = syntax_checker(line);
	if (syntax == 1 || syntax == 2)
		printf("Incorrect line\n");
	// specific errors needed
	else if (syntax != 3)
	{
		token_list = tokenize_input(line);
		handle_heredocs(token_list, env, exit_status);
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			return (free_tokens(&token_list), free(line), NULL);
		}
		clean_tokens(&token_list, env, exit_status);
	}
	free(line);
	return (token_list);
}
