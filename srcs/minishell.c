/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:25 by bmouhib           #+#    #+#             */
/*   Updated: 2025/02/03 19:00:53 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

void	executor(t_env **env, int *exit_status)
{
	t_token				*token;
	t_ast				*ast_root;
	char				*home;

	home = get_var(*env, "HOME");
	token = parse(env, exit_status, home);
	if (token)
	{
		ast_root = parse_tokens(token);
		if (ast_root)
		{
			exec(&ast_root, env, exit_status);
			free_ast(&ast_root);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	int					i;
	int					exit_status;
	struct sigaction	sa;
	t_env				*env;

	(void)av;
	if (ac > 1)
		return (0);
	i = 0;
	g_signal = 0;
	exit_status = 0;
	sa = init_sigaction();
	env = NULL;
	while (envp && envp[i])
		env = add_env(env, new_env(envp[i++]));
	if (!env)
	{
		env = add_env(env, new_env(ft_strjoin("PWD=", getcwd(NULL, 0))));
		env = add_env(env, empty_env("OLDPWD"));
		env = add_env(env, new_env("SHLVL=1"));
	}
	while (1)
		executor(&env, &exit_status);
	rl_clear_history();
	return (0);
}
