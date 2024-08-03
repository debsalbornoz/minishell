/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:34:42 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/28 17:55:23 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	valid_arg_newline(char *arg);

int	mini_echo(char **exec)
{
	int		newline;
	char	**copy_exec;

	newline = 0;
	copy_exec = exec;
	if (!*(copy_exec + 1))
		return (printf("\n"), 0);
	while (++copy_exec, copy_exec && *copy_exec != 0)
	{
		if (!valid_arg_newline(*copy_exec))
			newline++;
		else
		{
			ft_putstr_fd(*copy_exec, 1);
			if (*(copy_exec + 1))
				ft_putstr_fd(" ", 1);
			else
				break ;
		}
	}
	if (!newline)
		printf("\n");
	return (0);
}

static int	valid_arg_newline(char *arg)
{
	char	*arg_tmp;
	int		iterator;

	iterator = 0;
	arg_tmp = arg;
	if (*arg_tmp == '\0')
		return (1);
	while (*arg_tmp != '\0')
	{
		if (!iterator && *(arg_tmp) != '-')
			return (1);
		else if (iterator && *(arg_tmp) != 'n')
			return (1);
		arg_tmp++;
		iterator++;
	}
	return (0);
}
