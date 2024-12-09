/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:25 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/09 23:43:36 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	main(void)
{
	char				*line;
	struct sigaction	sa;
	t_token				*token_list;
	// t_ast				*ast_root;

	g_signal = 0;
	sa_init(&sa);
	while (!g_signal)
	{
		line = readline(prompt());
		if (!line)
			exit(write(STDOUT_FILENO, "exit\n", 5)); // need exit function
		if (ft_strlen(line))
			add_history(line);
		if (syntax_checker(line)) //NEED TO CHECK FOR UNSUPPORTED CHAR
			printf("Incorrect line\n");
		token_list = tokenize_input(line);
		print_tokens(token_list);
		// ast_root = parse_tokens(token_list);
		g_signal = 0;
		free(line);
		// free(ast);
	}
	return (0);
}
