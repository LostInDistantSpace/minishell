/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:49:05 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/18 19:22:36 by bmouhib          ###   ########.fr       */
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

void	parse(t_env *env)
{
	char	*line;
	t_token	*token_list;

	line = get_input(prompt(env));
	if (!line)
	{
		free_env(env);
		exit(write(STDOUT_FILENO, "exit\n", 5)); // need exit function
	}
	if (syntax_checker(line))
		printf("Incorrect line\n");
	else
	{
		token_list = tokenize_input(line);
		handle_heredocs(token_list);
		print_tokens(token_list);
		// ast_root = parse_tokens(token_list);
		free_tokens(token_list);
	}
	free(line);

	/* transforming string
	** - expand var if needed (if string is empty AT THIS STAGE ONLY, remove word)
	**		- $ if whtespace ou \0 after, no expand
	**		- if smth else after, expand into V
	**		- WE DO EXPAND AL TOKENS ARGS (except heredocs delimiter)
	** - remove quotes
	*/
}
