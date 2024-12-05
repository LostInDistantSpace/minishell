/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:25 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/05 20:08:14 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	main(int argc, char **argv)
{
	char				*line;
	struct sigaction	sa;
	// t_ast_node	*ast;

	(void)argv;
	if (argc != 1)
		return (1);
	g_signal = 0;
	sa = sa_init();
	sigaction(SIGINT, &sa, NULL);
	sigaction(EOF, &sa, NULL);
	while (!g_signal)
	{
		line = readline(prompt());
		if (!line)
			exit(write(STDOUT_FILENO, "exit\n", 5)); // need exit function
		if (syntax_checker(line))
		{
			printf("Incorrect line\n");
			// free(line);
			// exit(write(STDOUT_FILENO, "exit\n", 5)); // need exit function
		}
		// ast = parse_tokens(tokenize_input(line));
		g_signal = 0;
		free(line);
		// free(ast);
	}
	return (0);
}
