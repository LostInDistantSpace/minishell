/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:25 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/04 22:55:39 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

char	*prompt(void)
{
	char	*dir;
	char	*tmp;
	char	*prompt;

	dir = get_dir();
	prompt = ft_double_join(GREEN, BOLD, getenv("USER"));
	tmp = ft_double_join(prompt, "@", getenv("NAME"));
	free(prompt);
	prompt = ft_double_join(tmp, " ", BLUE);
	free(tmp);
	tmp = ft_double_join(prompt, dir, "$ ");
	prompt = ft_strjoin(tmp, RESET_COLOR);
	return (free(tmp), free(dir), prompt);
}

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
		{
			write(STDERR_FILENO, "exit\n", 5);
			exit(0);
		}
		if (!ft_strcmp(line, "exit")) //to remove (tests)
		{
			free(line);
			exit(0);
		}
		// syntax_checker(line);
		// ast = parse_tokens(tokenize_input(line));
		g_signal = 0;
		free(line);
		// free(ast);
	}
	return (0);
}
