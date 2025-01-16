/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:25 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/16 14:03:37 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

void	executor(t_env **env, int exit_status)
{
	t_token				*token;
	t_ast				*ast_root;

	token = parse(*env, exit_status);
	if (token)
	{
		ast_root = parse_tokens(token);
		if (ast_root)
		{
			exec(&ast_root, env, &exit_status);
			free_ast(&ast_root);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	int					exit_status;
	struct sigaction	sa;
	t_env				*env;

	if (ac > 1)
		return (0);
	(void)av;
	g_signal = 0;
	env = init(&sa, envp, &exit_status);
	while (1)
		executor(&env, exit_status);
	rl_clear_history();
	return (0);
}
