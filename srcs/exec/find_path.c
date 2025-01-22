/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:33:19 by lemarian          #+#    #+#             */
/*   Updated: 2025/01/22 14:54:23 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*check_command(char *command)
{
	struct stat	stats;

	stat(command, &stats);
	if (S_ISDIR(stats.st_mode))
	{	
		printf("%s : is a directory\n", command);
		return (NULL);
	}
	else
		return (command);
}

char	*test_path(char *path, char *cmd, t_data *data)
{
	char	*slash;
	char	*test_path;

	slash = ft_strjoin(path, "/");
	if (!slash)
		ft_error(data);
	test_path = ft_strjoin(slash, cmd);
	free(slash);
	if (!test_path)
		ft_error(data);
	if (access(test_path, X_OK) != -1)
		return (test_path);
	else
		return (free(test_path), NULL);
}

char	*find_cmd_path(char *cmd, char **paths, t_data *data)
{
	int		i;
	char	*cmd_path;

	i = 0;
	cmd_path = NULL;
	while (paths[i])
	{
		cmd_path = test_path(paths[i], cmd, data);
		if (cmd_path)
			break ;
		i++;
	}
	return (cmd_path);
}

char	*get_path(char *cmd, t_data *data)
{
	char	*path_str;
	char	**paths;
	char	*correct_path;
	t_env	*current;

	path_str = NULL;
	current = *data->env;
	while (current)
	{
		if (ft_strcmp(current->key, "PATH") == 0)
			path_str = current->value;
		current = current->next;
	}
	if (!path_str)//if PATH var was deleted or NULL
		return (NULL);
	paths = ft_split(path_str, ':');
	if (!paths)
		return (ft_error(data), NULL);
	correct_path = find_cmd_path(cmd, paths, data);
	free_array(&paths);
	if (!correct_path)
		printf("%s : command not found\n", cmd);
	return (correct_path);
}
