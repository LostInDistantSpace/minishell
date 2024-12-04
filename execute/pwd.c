/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:51:39 by lemarian          #+#    #+#             */
/*   Updated: 2024/12/04 15:42:47 by lemarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	pwd(void)//idk if i need parameters
{
	char	*dir;
	size_t	size;

	dir = NULL;
	size = 0;
	printf("%s\n", getcwd(dir, size));
}

/*int	main(void)
{
	pwd();
	return (0);
}*/
