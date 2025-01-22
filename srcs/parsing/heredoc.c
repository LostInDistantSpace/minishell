/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:32:10 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/21 17:29:31 by bmouhib          ###   ########.fr       */
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
		printf("minishell: warning: ");
		printf("here-document delimited by end-of-file (wanted `%s')\n", delim);
	}
	return (*name);
}

char	*create_heredoc(char *delim, t_env *env, int exit_status)
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
	while (ft_strcmp(input, delim) != 0)
	{
		if (g_signal || !input)
			return (heredoc_exit(input, &name, delim, heredoc));
		// Maybe delete the files if smth went wrong ???
		input = expand(input, env, 0, exit_status);
		if (!input)
			return (NULL);
		ft_putstr_fd(input, heredoc);
		write(heredoc, "\n", 1);
		free(input);
		input = readline("> ");
	}
	close(heredoc);
	return (free(input), name);
}

void	handle_heredocs(t_token *token, t_env *env, int exit_status)
{
	char	*name;

	while (token)
	{
		if (token->type == REDIR_HEREDOC)
		{
			name = create_heredoc(token->value[0], env, exit_status);
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
