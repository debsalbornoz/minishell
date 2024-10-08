/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexadecimal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:35:38 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/04 15:48:43 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	count_hexadecimal(unsigned long int nbr)
{
	unsigned int	i;

	i = 1;
	while (nbr > 15)
	{
		nbr = nbr / 16;
		i++;
	}
	return (i);
}

int	ft_hexadecimal(unsigned int n, char *base, unsigned int base_len)
{
	char	c;

	if (n >= base_len)
		ft_hexadecimal(n / base_len, base, base_len);
	c = base[n % base_len];
	write(1, &c, 1);
	return (count_hexadecimal(n));
}
