/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:05:21 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/20 17:57:37 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(t_env *env, char *key)
{
	if (!key || !env)
		return (NULL);
	if (!ft_strcmp(key, "?") || key[0] < 0)
		return (ft_strdup(key));
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_env	*new_env(char *str)
{
	int		i;
	int		len;
	t_env	*var;

	if (!str)
		return (NULL);
	len = 0;
	var = malloc(sizeof(t_env));
	if (!var)
		return (NULL);
	var->next = NULL;
	while (str[len] && str[len] != '=')
		len++;
	var->key = malloc((len + 1) * sizeof(char));
	if (!var->key)
		return (free(var), NULL);
	var->key[len] = 0;
	i = -1;
	while (++i < len)
		var->key[i] = str[i];
	i++;
	var->value = ft_strdup(str + i);
	if (!var->value)
		return (free(var->key), free(var), NULL);
	return (var);
}

t_env	*empty_env(char *str)
{
	int		i;
	int		len;
	t_env	*var;

	if (!str)
		return (NULL);
	len = 0;
	var = malloc(sizeof(t_env));
	if (!var)
		return (NULL);
	var->next = NULL;
	while (str[len] && str[len] != '=')
		len++;
	var->key = malloc((len + 1) * sizeof(char));
	if (!var->key)
		return (free(var), NULL);
	var->key[len] = 0;
	i = -1;
	while (++i < len)
		var->key[i] = str[i];
	var->value = NULL;
	return (var);
}

t_env	*add_env(t_env *head, t_env *var)
{
	t_env	*tmp;

	if (!var)
		return (head);
	if (!head)
	{
		head = var;
		return (head);
	}
	tmp = head;
	while (tmp->next)
			tmp = tmp->next;
	tmp->next = var;
	return (head);
}
