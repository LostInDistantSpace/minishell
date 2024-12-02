/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:45:44 by bmouhib           #+#    #+#             */
/*   Updated: 2024/10/12 15:31:12 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_char_search(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == (char)c)
			return (1);
		s++;
	}
	return (0);
}

size_t	ft_buffer_len(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	i += (s[i] == '\n');
	return (i);
}

char	*ft_copy_buffer(char *str)
{
	int		i;
	char	*cpy;

	i = 0;
	if (!str || !*str)
		return (NULL);
	cpy = malloc((ft_buffer_len(str) + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	while (*str && *str != '\n')
		cpy[i++] = *str++;
	if (*str == '\n')
		cpy[i++] = '\n';
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_join_buffer(char *line, char *buffer)
{
	size_t	i;
	size_t	len;
	char	*s;

	len = ft_buffer_len(buffer) + ft_buffer_len(line);
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (free(line), NULL);
	i = 0;
	if (line)
	{
		i--;
		while (line[++i])
			s[i] = line[i];
		free(line);
	}
	if (buffer)
	{
		while (*buffer && *buffer != '\n')
			s[i++] = *buffer++;
		if (*buffer == '\n')
			s[i] = '\n';
	}
	s[len] = '\0';
	return (s);
}
