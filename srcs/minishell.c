/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:25 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/18 18:48:49 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

/*
Prints the tokens to verify the tokenization process.
*/
void	print_tokens(t_token *token)
{
	int		i;
	t_token	*ptr;

	ptr = token;
	while (ptr)
	{
		i = 0;
		while (ptr->value[i])
			printf("Token: [%s] | ", ptr->value[i++]);
		printf("Type : ");
		if (ptr->type == WORD)
			printf("WORD\n");
		else if (ptr->type == PIPE)
			printf("PIPE\n");
		else if (ptr->type == REDIR_IN)
			printf("REDIR_IN\n");
		else if (ptr->type == REDIR_OUT)
			printf("REDIR_OUT\n");
		else if (ptr->type == REDIR_APPEND)
			printf("REDIR_APPEND\n");
		else if (ptr->type == REDIR_HEREDOC)
			printf("REDIR_HEREDOC\n");
		printf("--------------------------------------------------\n");
		ptr = ptr->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	struct sigaction	sa;
	t_env				*env;
	// t_ast				*ast_root;

	if (ac > 1)
		return (0);
	(void)av;
	g_signal = 0;
	env = init(&sa, envp);
	/*
	** NEED TO MANAGE THE C-\ signal
	**
	** $? -> get last errno (NOT ENV VAR)
	*/
	while (!g_signal)
	{
		parse(env);
		// free(ast);
	}
	rl_clear_history();
	return (0);
}
