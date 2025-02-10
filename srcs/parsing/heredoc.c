/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:32:10 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/10 19:51:35 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_heredoc_name(void)
{
	int		i;
	char	*name;
	char	*num;

	i = 0;
	name = ft_strdup("/tmp/heredoc");
	while (access(name, F_OK) == 0)
	{
		i++;
		free(name);
		num = ft_itoa(i);
		name = ft_strjoin("/tmp/heredoc", num);
		free(num);
	}
	return (name);
}

char	*heredoc_exit(char *input, char **name, char *delim, int heredoc)
{
	close(heredoc);
	if (g_signal)
	{
		unlink(*name);
		free(*name);
		*name = NULL;
	}
	if (!input)
	{
		ft_putstr_fd("warning: here-document delimited ", STDERR_FILENO);
		ft_putstr_fd("by end-of-file (wanted '", STDERR_FILENO);
		ft_putstr_fd(delim, STDERR_FILENO);
		ft_putstr_fd("')\n", STDERR_FILENO);
	}
	return (*name);
}

char	*create_heredoc(char *delim, t_env *env, int exit_status, int quoted)
{
	int		heredoc;
	char	*input;
	char	*name;

	name = get_heredoc_name();
	heredoc = open(name, O_WRONLY | O_CREAT, 0644);
	if (heredoc == -1)
		return (perror(name), free(name), NULL);
	input = readline("> ");
	while (ft_strcmp(input, delim) != 0)
	{
		if (g_signal || !input)
			return (heredoc_exit(input, &name, delim, heredoc));
		if (!quoted)
			input = expand(input, env, 0, exit_status);
		if (!input)
			return (free(name), NULL);
		ft_putstr_fd(input, heredoc);
		write(heredoc, "\n", 1);
		free(input);
		input = readline("> ");
	}
	close(heredoc);
	return (free(input), name);
}

void	handle_heredocs(t_token **head, t_env *env, int *exit_status)
{
	int		quoted;
	char	*name;
	t_token	*token;

	token = *head;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			quoted = token->quoted;
			name = create_heredoc(token->value[0], env, *exit_status, quoted);
			if (!name)
			{
				free_tokens(head);
				*head = new_token(NULL, -1, 0);
				*exit_status = 3;
				return ;
			}
			free(token->value[0]);
			token->value[0] = name;
		}
		token = token->next;
	}
}
