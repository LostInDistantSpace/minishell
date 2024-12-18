/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:43:23 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/13 17:47:51 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//finalement c hors sujet pour le heredoc mais je te laisse ca la

char	*expand_var(char *str, t_env *env)
{
	int	i;
	t_env	*current;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	while (current)
	{
		if (ft_strncmp(str, current->key, i) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
