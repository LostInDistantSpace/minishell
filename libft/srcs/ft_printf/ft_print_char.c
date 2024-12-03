/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:16:07 by bmouhib           #+#    #+#             */
/*   Updated: 2024/09/10 15:19:44 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_char(char c, t_flag flag, int *count)
{
	if (flag.left)
		ft_print_c(c, count);
	while (flag.width-- > 1)
		ft_print_c(' ', count);
	if (!flag.left)
		ft_print_c(c, count);
}
