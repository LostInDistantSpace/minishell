/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:32:45 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/04 15:43:00 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


/*
about redirections: if it's << it redirects input to a heredoc,
if it's >> it redirects output to a file and it appends, doesn't truncate.

void	exec(t_ast_node **head)
{
	if (head == word) -> should be a command
	{
		if (word == built-in)
			exec(built-in)
		else
		{
			if (!search_path(word))
				error(command not found);
			else
				exec(path, cmd);(in child process)
		}
	}
	if (head == redirection) -> not good, several redirections?
	{
		go->right;
		if (not word)
			go->left;
		if (still not word)
			error(no valid file name for redirection);
		else
			redirect(args[0]);
		if (args[1] != command)
			error(command not found);
	}
	if (head == pipe)
	{
		if (head->left == NULL)
			error(no command);
		fork();
		pipe();
		while (node->left != NULL)
		{
			if (node == redirection)
				redirect(node->right(args[0]));
			go->left;
		}
		if (node != word)
			error(no command);
		if (word == built-in)
			exec(built-in);
		else
		{
			if (!search_path(word))
				error(command not found);
			else
				exec(command);(in child process)
		}
		go->right;
		if (pipe)
			fork;
		etc;
	}
}
*/

