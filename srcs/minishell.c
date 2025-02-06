/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:25 by bmouhib           #+#    #+#             */
/*   Updated: 2025/02/06 15:37:09 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*env;

	i = 0;
	env = NULL;
	while (envp && envp[i])
		env = add_env(env, new_env(envp[i++]));
	if (!env)
	{
		env = add_env(env, new_env(ft_strjoin("PWD=", getcwd(NULL, 0))));
		env = add_env(env, empty_env("OLDPWD"));
		env = add_env(env, new_env("SHLVL=1"));
	}
	return (env);
}

int	executor(t_env **env, int *exit_status)
{
	t_token				*token;
	t_ast				*ast_root;
	char				*home;

	home = get_var(*env, "HOME");
	token = parse(env, exit_status, home);
	if (token && token->type >= 0)
	{
		ast_root = parse_tokens(token);
		if (ast_root && ast_root->type >= 0)
		{
			sigquit_manager(1);
			exec(&ast_root, env, exit_status);
			free_ast(&ast_root);
			if (g_signal)
				*exit_status = 128 + g_signal;
			sigquit_manager(0);
		}
		else if (ast_root->type < 0)
			return (free_tokens(&token), free_ast(&ast_root), 1);
	}
	else if (token && token->type < 0)
		return (free(token), free_env(env), 1);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	int		error;
	int		exit_status;
	t_env	*env;

	(void)av;
	if (ac > 1)
	{
		printf("minishell: too many arguments\n");
		return (1);
	}
	g_signal = 0;
	exit_status = 0;
	init_sigaction();
	env = init_env(envp);
	error = 0;
	while (!error)
		error = executor(&env, &exit_status);
	rl_clear_history();
	return (0);
}
