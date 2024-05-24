/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:57:42 by jraupp            #+#    #+#             */
/*   Updated: 2024/05/23 15:12:52 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	main(int argc, char **argv)
{
	(void)argc;
	echo(argv);
	return (EXIT_SUCCESS);
}

void	echo(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			write(1, &argv[i][j], 1);
			j++;
		}
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}
