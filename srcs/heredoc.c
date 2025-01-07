/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:32:10 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/07 23:24:57 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_heredoc_name(void)
{
	int		i;
	char	*name;

	i = 0;
	name = ft_strdup("/tmp/heredoc");
	while (access(name, F_OK) == 0)
	{
		i++;
		free(name);
		name = ft_strjoin("/tmp/heredoc", ft_itoa(i));
	}
	return (name);
}

char	*create_heredoc(t_token *token, t_env *env)
{
	int		heredoc;
	char	*input;
	char	*name;

	name = get_heredoc_name();
	heredoc = open(name, O_WRONLY | O_CREAT, 0644);
	if (heredoc == -1)
		return (perror(name), free(name), NULL);
	//also need absolute path
	input = readline("> ");
	while (ft_strcmp(input, token->value[0]) != 0)
	{
		if (g_signal || !input)
		{
			close(heredoc);
			if (g_signal)
			{
				unlink(name);
				free(name);
				return (NULL);
			}
			if (!input)
			{
				// print warning
				return (name);
			}
		}
		/*
		** Maybe delete the files if smth went wrong ???
		*/
		input = expand_var(input, env);
		if (!input)
			return (NULL);
		ft_putstr_fd(input, heredoc);
		write(heredoc, "\n", 1);
		free(input);
		input = readline("> ");
	}
	free(input);
	close(heredoc);
	return (name);
}

void	handle_heredocs(t_token *token, t_env *env)
{
	char	*name;

	while (token)
	{
		if (token->type == REDIR_HEREDOC)
		{
			name = create_heredoc(token, env);
			if (!name)
				return ;
			free(token->value);
			token->value = malloc(2 * sizeof(char *));
			token->value[0] = name;
			token->value[1] = NULL;
		}
		token = token->next;
	}
}
