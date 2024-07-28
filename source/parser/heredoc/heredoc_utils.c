/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:55:37 by codespace         #+#    #+#             */
/*   Updated: 2024/07/28 17:59:52 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_quoted(char *eof)
{
	int	i;

	i = 0;
	while (eof[i])
	{
		if (eof[i] == '\'' || eof[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

int	get_var_len(char *input)
{
	int	i;

	i = 0;
	while (input[i] != ' ' && input[i] != '$'
		&& input[i] != '\0' && input[i] != '\"' && input[i] != '\'')
		i++;
	return (i);
}

int	get_substr_len(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '$' && input[i] != '\0')
		i++;
	return (i);
}
