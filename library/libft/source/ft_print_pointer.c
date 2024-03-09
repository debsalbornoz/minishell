/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:57:15 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/04 15:48:40 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_printptr(unsigned long int n, char *base, unsigned int base_len)
{
	char	c;

	if (n >= base_len)
		ft_printptr(n / base_len, base, base_len);
	c = base[n % base_len];
	write(1, &c, 1);
}

int	ft_putptr(unsigned long int n, char *base, unsigned int base_len)
{
	if (n == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	ft_putchar('0');
	ft_putchar('x');
	ft_printptr(n, base, base_len);
	return (count_hexadecimal(n) + 2);
}
