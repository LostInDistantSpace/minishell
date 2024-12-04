/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:25 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/04 21:48:33 by bmouhib          ###   ########.fr       */
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


char	*get_dir(void)
{
	int		home_len;
	char	*home;
	char	*cwd;
	char	*gwd;

	home = getenv("HOME");
	home_len = ft_strlen(home);
	cwd = getcwd(NULL, 0);
	if (!ft_strncmp(cwd, home, home_len))
	{
		gwd = malloc(ft_strlen(cwd) - home_len + 2 * sizeof(char));
		gwd = ft_strjoin("~", cwd + home_len);
		free(cwd);
		return (ft_double_join(BOLD, gwd, RESET_COLOR));
	}
	return (ft_double_join(BOLD, cwd, RESET_COLOR));
}

char	*prompt(void)
{
	char	*dir;
	char	*tmp;
	char	*prompt;

	dir = get_dir();
	prompt = ft_double_join(GREEN, BOLD, getenv("USER"));
	tmp = ft_double_join(prompt, "@", getenv("NAME"));
	free(prompt);
	prompt = ft_double_join(tmp, " ", BLUE);
	free(tmp);
	tmp = ft_double_join(prompt, dir, "$ ");
	prompt = ft_strjoin(tmp, RESET_COLOR);
	return (free(tmp), free(dir), prompt);
}

int	main(int argc, char **argv)
{
	int			end_signal;
	char		*line;
	// t_ast_node	*ast;
	// struct sigaction	sa;

	(void)argv;
	if (argc != 1)
		return (1);
	end_signal = 0;
	// signal_handling(&sa);
	while (!end_signal)
	{
		line = readline(prompt());
		if (!line)
			end_signal = 1;
		// syntax_checker(line);
		// ast = parse_tokens(tokenize_input(line));
		// free(ast);
		free(line);
	}
	return (0);
}
