/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:32:10 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/11 18:01:20 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	handle_heredoc(char *str)
{
	int	heredoc;
	int	i;
	char	*input;

	heredoc = open("tmp/heredoc", O_WRONLY | O_CREAT, 0644);
	input = readline(">");
	while (ft_strncmp(input, str, ft_strlen(input)) != 0)
	{
		i = 0;
		while (input[i])
		{
			write(heredoc, &input[i], 1);
			i++;
		}
		free(input);
		input = readline(">");
	}
	free(input);
}

int	main(void)
{
	char *str = "EOF";
	handle_heredoc(str);
	return (0);
}
