/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:34:21 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/21 18:09:02 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	change_directory(char *cwd, char *path);

int	mini_cd(char **exec)
{
	char	cwd[2048];
	char	**copy_exec;

	copy_exec = exec;
	if (!ft_str_exist(*(copy_exec + 1)))
		return (change_directory(cwd, getenv("HOME")));
	else if (++copy_exec, ft_str_exist(*(copy_exec + 1)))
		return (ft_putstr_fd(" too many arguments\n", 2), 1);
	return (change_directory(cwd, *copy_exec));
}

static int	change_directory(char *cwd, char *path)
{
	if (chdir(path))
		return (perror("chdir"), 1);
	if (!getcwd(cwd, sizeof(char) * 2048))
		return (perror("getcwd"), 1);
	return (0);
}
