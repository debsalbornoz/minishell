/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:36:01 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/01 12:09:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	mini_pwd(char **exec)
{
	char	path[2048];

	(void)exec;
	if (!getcwd(path, sizeof(path)))
		return (perror("getcwd"), 1);
	return (printf("%s\n", path), 0);
}
