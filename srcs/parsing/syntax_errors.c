/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:06:12 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/20 16:10:49 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_not_handled(char c)
{
	printf("minishell: character not handled '%c'\n", c);
	return (1);
}

int	unclosed_quote(void)
{
	printf("minishell: syntax error: unclosed quote\n");
	return (1);
}
