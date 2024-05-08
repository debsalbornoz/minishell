/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:12:07 by jraupp            #+#    #+#             */
/*   Updated: 2024/05/06 17:14:10 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_node	*is_builtin(t_node *node)
{
	int		i;
	char	*token;
	int		token_len;
	char	*builtins[8];

	i = 0;
	token = node->data->token->value;
	token_len = ft_strlen(token);
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	while (builtins[i] != NULL)
	{
		if (identify_builtin(token, builtins[i++], token_len)
			&& node->data->token->type == COMMAND)
			node->data->token->type = BUILTIN;
	}
	return (node);
}

int	identify_builtin(char *token, char *builtin, int token_len)
{
	int		i;
	char	signal;

	i = 0;
	signal = 0;
	signal = process_quotes(signal, token[i]);
	if (!signal)
	{
		if (token_len == ft_strlen(builtin))
			if (!ft_strncmp(token, builtin, token_len))
				return (1);
	}
	if (signal)
		if (compare_quoted_strings(token, builtin))
			return (1);
	return (0);
}

int	compare_quoted_strings(char *token, char *builtin)
{
	int		i;
	int		j;
	int		token_len;

	i = 0;
	j = 1;
	token_len = ft_strlen(token);
	if (is_quote(token[0]) && is_quote(token[token_len - 1])
		&& token[0] == token[token_len - 1])
	{
		token_len -= 2;
		if (token_len == ft_strlen(builtin))
		{
			while (builtin[i] != '\0')
			{
				if (token[j] != builtin[i])
					return (0);
				i++;
				j++;
			}
			return (1);
		}
	}
	return (0);
}
