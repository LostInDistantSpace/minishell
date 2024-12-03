/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:25 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/02 20:08:09 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 - *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	*ft_double_join(char *left, char *middle, char *right)
{
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(left, middle);
	str = ft_strjoin(tmp, right);
	free(tmp);
	return (str);
}

char	*get_var(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}


char	*get_dir(char *user)
{
	int		home_len;
	char	*home;
	char	*gwd;

	if (user)
	{
		home_len = ft_strlen("/home/") + ft_strlen(user);
		home = malloc(home_len * sizeof(char));
		home = ft_strjoin("/home/", user);
		printf("User : %s\nHOME : %s (%d)\n", user, home, home_len);
		gwd = getcwd(NULL, 0);
		printf("CWD  : %s\n", gwd);
		if (!ft_strncmp(gwd, home, home_len))
			printf("Starts with home babe\n");
		return (gwd);
		// if (!ft_strncmp(buf, home, home_len))
		// {
		// 	free(buf);
		// 	buf = malloc(ft_strlen(gwd) - home_len + 1 * sizeof(char));
		// 	buf = ft_strjoin("~", gwd + home_len);
		// 	free(gwd);
		// 	gwd = buf;
		// }
	}
	gwd = NULL;
	return (ft_double_join(BOLD, gwd, RESET_COLOR));
}

int	main(int argc, char **argv)
{
	// int			end_signal;
// 	char		*line;
// 	t_ast_node	*ast;
	// struct sigaction	sa;

	(void)argv;
	if (argc != 1)
		return (1);
	// signal_handling(&sa);
	// get_env_var(env);
	// end_signal = 0;
	printf("%s\n", get_dir(getenv("USER")));
	// while (!end_signal)
	// {
		// line = readline(get_dir(getenv("USER")));
	// 	if (!line)
	// 		end_signal = 1;
	// 	syntax_checker(line);
	// 	ast = parse_tokens(tokenize_input(line));
	// 	free(ast);
	// 	free(line);
	// }
	return (0);
}
