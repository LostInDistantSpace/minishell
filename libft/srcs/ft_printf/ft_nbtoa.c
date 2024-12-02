/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:26:16 by bmouhib           #+#    #+#             */
/*   Updated: 2024/09/10 15:19:44 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_size(unsigned long int nb, long long int base)
{
	int	size;

	size = 0;
	if (nb == 0)
		size = 1;
	while (nb > 0)
	{
		nb = nb / base;
		size++;
	}
	return (size);
}

char	*ft_itoa_printf(int n)
{
	long long	nb;
	int			size;
	char		*tab;

	nb = n;
	if (nb < 0)
		nb *= -1;
	size = ft_size(nb, 10);
	tab = malloc(sizeof(char) * (size + 1));
	if (!tab)
		return (NULL);
	tab[size] = '\0';
	ft_putnbr(nb, tab, size - 1, 10);
	return (tab);
}

char	*ft_utoa(unsigned int n)
{
	long long	nb;
	int			size;
	char		*tab;

	nb = n;
	size = ft_size(nb, 10);
	tab = malloc(sizeof(char) * size + 1);
	if (!tab)
		return (NULL);
	tab[size] = '\0';
	ft_putnbr(nb, tab, size - 1, 10);
	return (tab);
}

char	*ft_xtoa(unsigned long int n, int x)
{
	unsigned long	size;
	char			*tab;

	size = ft_size(n, 16);
	tab = malloc(sizeof(char) * size + 1);
	if (!tab)
		return (NULL);
	tab[size] = '\0';
	if (x == 'x')
		ft_putnbr(n, tab, size - 1, 16);
	else
		ft_putnbr_caps(n, tab, size - 1, 16);
	return (tab);
}
