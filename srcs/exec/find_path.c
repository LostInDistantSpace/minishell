/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:33:19 by lemarian          #+#    #+#             */
/*   Updated: 2025/02/10 13:57:56 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*check_command(char *command, t_data *data)
{
	struct stat	stats;

	stat(command, &stats);
	if (S_ISDIR(stats.st_mode))
	{	
		ft_print_error("%s : is a directory\n", command);
		*data->exit_status = 126;
		return (exit_command(data));
	}
	if (access(command, X_OK) == -1)
	{
		ft_print_error("%s : permission denied\n", command);
		*data->exit_status = 126;
		return (exit_command(data));
	}
	return (dup_path(command, data));
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

char	*get_cmd(char *cmd, char *path_str, t_data *data)
{
	char	**paths;
	char	*correct_path;

	paths = ft_split(path_str, ':');
	if (!paths)
		ft_error(data);
	correct_path = find_cmd_path(cmd, paths, data);
	free_array(&paths);
	if (!correct_path)
	{	
		*data->exit_status = 127;
		ft_print_error("%s : command not found\n", cmd);
		return (NULL);
	}
	return (correct_path);
}

char	*get_path(char *cmd, t_data *data)
{
	char	*path_str;
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
	if (!path_str)
	{
		ft_print_error("%s : No such file or directory\n", cmd);
		*data->exit_status = 127;
		return (NULL);
	}
	correct_path = get_cmd(cmd, path_str, data);
	return (correct_path);
}
