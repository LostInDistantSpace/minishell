/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:35:28 by bmouhib           #+#    #+#             */
/*   Updated: 2024/11/25 19:40:56 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
* Iterates through the input string, 
* checking for syntax errors and 
* reporting them if found.
*/
int	syntax_checker(void)
{
	return (0);
}

/*
Function: Checks for unclosed quotes in the input string.
*/
int	has_unclosed_quotes(void)
{
	return (0);
}

/*
Detects invalid redirections, 
such as multiple consecutive redirections or 
redirections at the start or end of the input.
*/
int	has_invalid_redirections(void)
{
	return (0);
}
/*
Detects misplaced pipes and redirections.
*/
int	has_misplaced_operators(void)
{
	return (0);
}

/* 
Detects logical operators such as && and || 
and reports them as not supported.
*/
int	has_logical_operators(void)
{
	return (0);
}
