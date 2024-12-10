/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:43:30 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/10 18:33:46 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(token));
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **first, t_token *token)
{
	if (!token)
		return ;
	if (!*first)
	{
		*first = token;
	}
	while ((*first)->next)
		*first = (*first)->next;
	(*first)->next = token;
}

/*
Handles the special characters in the input string.
*/
t_token	*handle_special_chars(char *input, int *pos)
{
	int	i;

	i = *pos;
	if (input[i] == '<' || input[i] == '>')
	{
		if (input[i + 1] && input[i + 1] == input[i])
		{
			*pos += 2;
			if (input[i] == '>')
				return (new_token(NULL, REDIR_APPEND));
			if (input[i] == '<')
				return (new_token(NULL, REDIR_HEREDOC));
		}
		else
		{
			(*pos)++;
			if (input[i] == '>')
				return (new_token(NULL, REDIR_OUT));
			if (input[i] == '<')
				return (new_token(NULL, REDIR_IN));
		}
	}
	return (NULL);
}

/*
Handles the words in the input string.
*/
t_token	*handle_word(char *input, int *pos)
{
	int		i;
	char	*value;

	i = *pos;
	while (ft_iswhitespace(input[i]))
		i++;
	while (!ft_iswhitespace(input[i]) && !is_special_char(input[i]))
		i++;
	value = ft_substr(input, *pos, i - *pos);
	*pos += i;
	return (new_token(value, WORD));
}

/*
 Iterates through the input, creating tokens for words separated by spaces.
*/
t_token	*tokenize_input(char *input)
{
	int		i;
	t_token	*token;
	t_token	*first_token;

	i = 0;
	while (input[i])
	{
		// WORK PIPE BY PIPE 
		// TOKENIZE REDIR + FILE/DELIM on first read
		// COMBINE REST OF CHARACTERS on second read
		if (input[i] == '<' || input[i] == '>')
			token = handle_special_chars(input, &i);
		else if (input[i] == '|')
			token = new_token("|", PIPE);
		else
			token = handle_word(input, &i);
		add_token(&first_token, token);
	}
	return (first_token);
}
/*
Prints the tokens to verify the tokenization process.
*/
void	print_tokens(t_token *token)
{
	t_token	*ptr;

	ptr = token;
	while (ptr)
	{
		printf("Token: %-30s | Type: ", token->value);
		if (token->type == WORD)
			printf("WORD\n");
		if (token->type == PIPE)
			printf("PIPE\n");
		if (token->type == REDIR_IN)
			printf("REDIR_IN\n");
		if (token->type == REDIR_OUT)
			printf("REDIR_OUT\n");
		if (token->type == REDIR_APPEND)
			printf("REDIR_APPEND\n");
		if (token->type == REDIR_HEREDOC)
			printf("REDIR_HEREDOC\n");
		printf("--------------------------------------------------\n");
		ptr = ptr->next;
	}
}
