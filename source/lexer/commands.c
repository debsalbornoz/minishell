/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:23:30 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/17 12:48:40 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*is_command(t_list *tokens)
{
	tokens->node = tokens->head;
	if (tokens->node)
	{
		while (tokens->node != NULL)
		{
			if (tokens->head->data->type == WORD)
				tokens->node->data->type = COMMAND;
			if (tokens->node->data->type == PIPE)
				if (tokens->node->next
					&& !is_redirect_or_pipe(tokens->node->next->data->type))
					tokens->node->next->data->type = COMMAND;
			tokens->node = tokens->node->next;
		}
	}
	tokens->node = tokens->head;
	return (tokens);
}

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
	if (is_quote(s1[0]) && is_quote(s1[len - 1]))
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

t_list	*is_builtin(t_list *tokens)
{
	char	*builtins[8];
	int		i;

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	while (tokens->node != NULL)
	{
		i = 0;
		while (builtins[i] != NULL)
		{
			if (ft_strlcmp(tokens->node->value, builtins[i++],
					ft_strlen(tokens->node->value))
				&& tokens->node->data->type == COMMAND)
				tokens->node->data->type = BUILTIN;
		}
		tokens->node = tokens->node->next;
	}
	tokens->node = tokens->head;
	return (tokens);
}
