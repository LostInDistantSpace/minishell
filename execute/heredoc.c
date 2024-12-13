/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:32:10 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/13 17:49:17 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*get_heredoc_name()
{
	int	i;
	char	*name;
	int	fd;

	i = 0;
	name = ft_strjoin("tmp/heredoc", ft_itoa(i));
	while (access(name, F_OK) == 0)
	{
		free(name);
		i++;
		name = ft_strjoin("tmp/heredoc", ft_itoa(i));
	}
	return (name);
}

char	*create_heredoc(t_ast *node)
{
	int	heredoc;
	char	*input;
	char	*name;

	if (access("tmp/heredoc", F_OK) == 0)
	{
		name = get_heredoc_name();
		heredoc = open(get_heredoc_name(), O_WRONLY | O_CREAT, 0644);
		free(name);
	}
	else
		heredoc = open("tmp/heredoc", O_WRONLY | O_CREAT, 0644);
	input = readline(">");
	while (ft_strncmp(input, node->args, ft_strlen(input)) != 0)
	{
		while (*input)
			write(heredoc, input++, 1);
		write(heredoc, "\n", 1);
		free(input);
		input = readline(">");
	}
	free(input);
	close(heredoc);
	return (name);
}

void	handle_heredoc(t_ast *node, t_data *data)
{
	char *name;
	int	heredoc;

	name = create_heredoc(node);
	heredoc = open(name, O_RDONLY);
	unlink(name);// not sure this is the right path
	dup2(heredoc, STDIN_FILENO);
	close(heredoc);
	if (node->right != NULL)
		ast(node->right, data);
	find_command(node->left, data);
}
