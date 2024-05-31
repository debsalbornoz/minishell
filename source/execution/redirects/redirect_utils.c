/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:20:16 by codespace         #+#    #+#             */
/*   Updated: 2024/05/31 20:09:52 by dlamark-         ###   ########.fr       */
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
