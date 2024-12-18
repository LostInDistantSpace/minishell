/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:30:49 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/10 15:44:44 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*test_path(char *path, char *cmd)
{
	char	*slash;
	char	*test_path;

	slash = ft_strjoin(path, "/");
	test_path = ft_strjoin(slash, cmd);
	free(slash);
	if (!test_path)
		return (NULL);
	if (access(test_path, X_OK) != -1)
		return (test_path);
	else
		return (free(test_path), NULL);
}

char	*find_cmd_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_path;

	i = 0;
	cmd_path = NULL;
	if (!cmd)
		return (NULL);
	while (paths[i])
	{
		cmd_path = test_path(paths[i], cmd);
		if (cmd_path)
			break ;
		i++;
	}
	return (cmd_path);
}

char	*get_path(char *cmd, char **ep)
{
	int		i;
	char	*path_str;
	char	*correct_path;
	char	**paths;

	i = 0;
	path_str = NULL;
	while (ep[i])
	{
		if (ft_strncmp(ep[i], "PATH=", 5) == 0)
			path_str = ft_strdup(&ep[i][5]);
		i++;
	}
	if (!path_str)
	{
		perror("Command not found:");
		ft_putstr_fd(cmd, 2);
		return (NULL);
	}
	paths = ft_split(path_str, ':');
	free(path_str);
	correct_path = find_cmd_path(cmd, paths);
	free_array(paths);
	return (correct_path);
}
