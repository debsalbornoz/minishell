/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:20:16 by codespace         #+#    #+#             */
/*   Updated: 2024/07/28 19:45:07 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	find_output(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 1)
	{
		if (ft_strncmp(str, ">", len) == 0)
			return (1);
	}
	return (0);
}

int	find_append(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 2)
	{
		if (ft_strncmp(str, ">>", len) == 0)
			return (1);
	}
	return (0);
}

int	find_input(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 1)
	{
		if (ft_strncmp(str, "<", len) == 0)
			return (1);
	}
	return (0);
}

int	find_heredoc(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 2)
	{
		if (ft_strncmp(str, "<<", len) == 0)
			return (1);
	}
	return (0);
}

int	update_lst_and_print_error(t_list *envp, int flag)
{
	if (flag == 1)
	{
		update_env_list(envp, "?", "1");
		ft_putstr_fd(" No such file or directory\n", 2);
		return (-1);
	}
	else if (flag == 2)
	{
		update_env_list(envp, "?", "1");
		ft_putstr_fd(" Is a directory\n", 2);
		return (-1);
	}
	else if (flag == 3)
	{
		update_env_list(envp, "?", "1");
		ft_putstr_fd(" Permission denied\n", 2);
		return (-1);
	}
	return (0);
}
