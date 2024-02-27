/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:19:21 by dlamark-          #+#    #+#             */
/*   Updated: 2024/02/27 19:19:23 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *s1)
{
	int	len;

	len = ft_strlen(s1);
	if (ft_strcmp(s1, "echo", len))
		return (1);
	else if (ft_strcmp(s1, "cd", len))
		return (2);
	else if (ft_strcmp(s1, "pwd", len))
		return (3);
	else if (ft_strcmp(s1, "export", len))
		return (4);
	else if (ft_strcmp(s1, "unset", len))
		return (5);
	else if (ft_strcmp(s1, "env", len))
		return (6);
	else if (ft_strcmp(s1, "exit", len))
		return (7);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && (i < n))
	{
		if (s1[i] != s2[i] || s2[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	return (1);
}
