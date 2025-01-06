/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:25 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/06 13:56:18 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	main(int ac, char **av, char **envp)
{
	struct sigaction	sa;
	t_env				*env;
	t_token				*token;
	t_ast				*ast_root;

	if (ac > 1)
		return (0);
	(void)av;
	g_signal = 0;
	env = init(&sa, envp);
	/*
	** $? -> get last errno (NOT ENV VAR)
	*/
	while (!g_signal)
	{
		token = parse(env);
		if (token)
			print_tokens(token);
		ast_root = parse_tokens(token);
		/*
		NOTE TO SELF : REMOVE -lm FROM MAKEFILE (used for math lib)
		*/
		if (ast_root)
			print_ast_tree(ast_root);
		free_tokens(token);
		// free_ast(ast_root);
	}
	rl_clear_history();
	return (0);
}
