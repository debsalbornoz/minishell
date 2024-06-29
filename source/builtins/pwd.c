/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:36:01 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/29 16:26:18 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	mini_pwd(char **exec)
{
	char	path[2048];
	(void)exec;
	//if (ft_str_exist(*(exec + 1)))
	//	return (printf("pwd: too many args for command\n"), 1);
	if (!getcwd(path, sizeof(path)))
		return (perror("getcwd"), 1);
	return (printf("%s\n", path), 0);
}
