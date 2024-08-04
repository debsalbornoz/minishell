/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:36:01 by dlamark-          #+#    #+#             */
/*   Updated: 2024/08/04 10:48:35 by jraupp           ###   ########.fr       */
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
