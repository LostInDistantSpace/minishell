/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:43:30 by bmouhib           #+#    #+#             */
/*   Updated: 2024/12/10 22:41:14 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **first, t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	if (!*first)
	{
		*first = token;
		return ;
	}
	tmp = *first;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = token;
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
	while (!ft_iswhitespace(input[i]) && !is_special_char(input[i]))
		i++;
	value = ft_substr(input, *pos, i - *pos);
	*pos = i;
	return (new_token(value, WORD));
}

/*
 Iterates through the input, creating tokens for words separated by spaces.
*/
t_token	*tokenize_input(char *input)
{
	int		i;
	int		len;
	t_token	*token;
	t_token	*head;

	i = 0;
	len = ft_strlen(input);
	head = NULL;
	while (input[i] && i < len)
	{
		// WORK PIPE BY PIPE 
		// TOKENIZE REDIR + FILE/DELIM on first read
		// COMBINE REST OF CHARACTERS on second read
		// ADD PIPE
		// Rince & repeat (while)
		while (ft_iswhitespace(input[i]))
			i++;
		if (input[i] == '<' || input[i] == '>')
			token = handle_special_chars(input, &i);
		else if (input[i] == '|')
		{
			token = new_token("|", PIPE);
			i++;
		}
		else
			token = handle_word(input, &i);
		add_token(&head, token);
	}
	return (head);
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
		printf("Token: %-30s | Type: ", ptr->value);
		if (ptr->type == WORD)
			printf("WORD\n");
		else if (ptr->type == PIPE)
			printf("PIPE\n");
		else if (ptr->type == REDIR_IN)
			printf("REDIR_IN\n");
		else if (ptr->type == REDIR_OUT)
			printf("REDIR_OUT\n");
		else if (ptr->type == REDIR_APPEND)
			printf("REDIR_APPEND\n");
		else if (ptr->type == REDIR_HEREDOC)
			printf("REDIR_HEREDOC\n");
		printf("--------------------------------------------------\n");
		ptr = ptr->next;
	}
}
