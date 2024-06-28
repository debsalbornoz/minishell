/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:34:42 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/23 15:03:04 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	mini_echo(char **exec)
{
	int		newline;
	char	**copy_exec;

	newline = 0;
	copy_exec = exec;
	if (!*(copy_exec + 1))
		return (printf("\n"), 0);
	while (++copy_exec, ft_str_exist(*copy_exec))
	{
		if (!ft_strcmp(*copy_exec, "-n"))
			newline++;
		else
		{
			printf("%s", *copy_exec);
			if (*(copy_exec + 1))
				printf(" ");
			else
				break ;
		}
	}
	if (!newline)
		return (printf("\n"), 0);
	return (0);
}
