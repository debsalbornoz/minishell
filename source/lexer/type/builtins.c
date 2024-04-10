/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:12:07 by jraupp            #+#    #+#             */
/*   Updated: 2024/04/10 20:05:58 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_strlcmp(char *s1, char *s2, int len)
{
	int		len_s2;
	int		i;
	char	signal;

	len_s2 = ft_strlen(s2);
	i = 0;
	signal = 0;
	signal = process_quotes(signal, s1[i]);
	if (!signal)
	{
		if (len == len_s2)
		{
			if (ft_strncmp(s1, s2, len) == 0)
				return (1);
		}
	}
	if (signal)
	{
		if (compare_quoted_strings(s1, s2) == 1)
			return (1);
	}
	return (0);
}

int	compare_quoted_strings(char *s1, char *s2)
{
	int	i;
	int	j;
	int	len;
	int	len_s2;

	i = 0;
	j = 1;
	len = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (is_quote(s1[0]) && is_quote(s1[len - 1]) && s1[0] == s1[len - 1])
	{
		len -= 2;
		if (len == len_s2)
		{
			while (s2[i] != '\0')
			{
				if (s1[j] != s2[i])
					return (0);
				i++;
				j++;
			}
			return (1);
		}
	}
	return (0);
}

t_node	*is_builtin(t_node *node)
{
	int		i;
	char	*builtins[8];

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strlcmp(node->data->token->value, builtins[i++],
				ft_strlen(node->data->token->value))
			&& node->data->token->type == COMMAND)
			node->data->token->type = BUILTIN;
	}
	return (node);
}
