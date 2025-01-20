/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:06:12 by bmouhib           #+#    #+#             */
/*   Updated: 2025/01/20 19:11:29 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_not_handled(char c)
{
	printf("minishell: character not handled '%c'\n", c);
	return (2);
}

int	unclosed_quote(void)
{
	printf("minishell: syntax error: unclosed quote\n");
	return (3);
}

int	unexpected_token(char *token)
{
	if (!token)
		token = "newline";
	printf("minishell: syntax error near unexpected token '%s'\n", token);
	return (4);
}
