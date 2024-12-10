/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:25 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/10 22:49:03 by bmouhib          ###   ########.fr       */
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
	t_token	*ptr;

	ptr = token;
	while (ptr)
	{
		printf("Token: %-30s | Type: ", ptr->value);
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
	char				*line;
	struct sigaction	sa;
	t_env				*env;
	t_token				*token_list;
	// t_ast				*ast_root;

	if (ac > 1)
		return (0);
	(void)av;
	g_signal = 0;
	env = init(&sa, envp); 
	// MIGHT NEED TO HARDCODE SOME ENV VARIABLES
	// $OLDPWD
	// $SHLVL
	// $_
	while (!g_signal)
	{
		line = readline(prompt(env));
		if (!line)
			exit(write(STDOUT_FILENO, "exit\n", 5)); // need exit function
		if (ft_strlen(line))
			add_history(line);
		if (syntax_checker(line)) //NEED TO CHECK FOR UNSUPPORTED CHAR
			printf("Incorrect line\n");
		else
		{
			token_list = tokenize_input(line);
			print_tokens(token_list);
			// ast_root = parse_tokens(token_list);
		}
		g_signal = 0;
		free(line);
		// free(ast);
	}
	return (0);
}
