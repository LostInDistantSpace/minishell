/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:17:28 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/10 15:33:28 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*test_path(char *path, char *cmd)
{
	char	*slash;
	char	*test_path;

	slash = ft_strjoin(path, "/");
	if (!slash)
		return (NULL);
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

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*path_str;
	char	*correct_path;
	char	**paths;

	i = 0;
	path_str = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_str = ft_strdup(&env[i][5]);
			if (!path_str)
				return (NULL);
		}
		i++;
	}
	paths = ft_split(path_str, ':');
	free(path_str);
	if (!paths)
		return (NULL);
	correct_path = find_cmd_path(cmd, paths);
	free_array(paths);
	return (correct_path);
}