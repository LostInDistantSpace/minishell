/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:25 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/13 17:40:22 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	main(int ac, char **av, char **envp)
{
	int					exit_status;
	struct sigaction	sa;
	t_env				*env;
	t_token				*token;
	t_ast				*ast_root;

	if (ac > 1)
		return (0);
	(void)av;
	g_signal = 0;
	env = init(&sa, envp, &exit_status);
	/*
	** $? -> get last errno (NOT ENV VAR)
	*/
	while (!g_signal)
	{
		token = parse(env, exit_status);
		if (token)
		{
			ast_root = parse_tokens(token);
			if (ast_root)
			{
				exec(&ast_root, &env);
				free_ast(ast_root);
			}
		}
	}
	rl_clear_history();
	return (0);
}
