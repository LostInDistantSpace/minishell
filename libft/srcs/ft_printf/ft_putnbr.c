/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:02:57 by bmouhib           #+#    #+#             */
/*   Updated: 2024/09/10 15:19:44 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(unsigned long nb, char *tab, int i, unsigned long base)
{
	if (nb % base < 10)
		tab[i] = (nb % base) + 48;
	else
		tab[i] = (nb % base) - 10 + 'a';
	if (nb >= base)
		ft_putnbr((nb / base), tab, i - 1, base);
}

void	ft_putnbr_caps(unsigned long nb, char *tab, int i, unsigned long base)
{
	if (nb % base < 10)
		tab[i] = (nb % base) + 48;
	else
		tab[i] = (nb % base) - 10 + 'A';
	if (nb >= base)
		ft_putnbr_caps((nb / base), tab, i - 1, base);
}
