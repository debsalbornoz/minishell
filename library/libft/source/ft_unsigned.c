/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:26:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/04 15:47:10 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	count_unsigned(unsigned int nbr)
{
	unsigned int	i;

	i = 1;
	while (nbr > 9)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

int	ft_unsigned(unsigned int n)
{
	char	c;

	c = n % 10 + '0';
	if (n >= 10)
	{
		ft_putnbr(n / 10);
	}
	write(1, &c, 1);
	return (count_unsigned(n));
}
