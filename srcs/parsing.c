/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:49:05 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/19 19:09:49 by bmouhib          ###   ########.fr       */
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

t_token	*parse(t_env *env)
{
	int		syntax;
	char	*line;
	t_token	*token_list;

	line = get_input(prompt(env));
	token_list = NULL;
	if (!line)
	{
		free_env(env);
		exit(write(STDOUT_FILENO, "exit\n", 5)); // need exit function
	}
	syntax = syntax_checker(line);
	if (syntax == 1 || syntax == 2)
		printf("Incorrect line\n"); // specific errors needed
	else if (syntax != 3)
	{
		token_list = tokenize_input(line);
		handle_heredocs(token_list);
		/* transforming string
		** - expand var if needed (if string is empty AT THIS STAGE ONLY, remove word)
		**		- $ if whtespace ou \0 after, no expand
		**		- if smth else after, expand into V
		**		- WE DO EXPAND AL TOKENS ARGS (except heredocs delimiter)
		** - remove quotes
		*/
	}
	free(line);
	return (token_list);
}
