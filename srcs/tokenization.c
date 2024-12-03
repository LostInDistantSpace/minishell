/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:43:30 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/02 19:22:57 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_token **first, char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(token));
	token->value = value;
	token->type = type;
	token->next = NULL;
	if (!*first)
	{
		*first = token;
	}
	while ((*first)->next)
		*first = (*first)->next;
	(*first)->next = token;
}

/*
 Iterates through the input, creating tokens for words separated by spaces.
*/
t_token	*tokenize_input(char *input)
{
	int		i;
	char	**split;
	t_token	*first_token;

	i = 0;
	split = ft_split(input, ' ');
	while (split[i])
	{
		//NEED TO DEVELOP
		add_token(&first_token, split[i], TOKEN_WORD);
	}
	return (first_token);
}

/*
Handles the special characters in the input string.
*/
void	handle_special_chars(void)
{
}

/*
Handles the words in the input string.
*/
void	handle_word(void)
{
}

/*
Prints the tokens to verify the tokenization process.
*/
void	print_tokens(void)
{
}
