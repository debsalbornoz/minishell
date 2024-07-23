/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:55:37 by codespace         #+#    #+#             */
/*   Updated: 2024/07/01 11:44:44 by codespace        ###   ########.fr       */
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
	while (input[i] != ' ' && input[i] != '$' && input[i] != '\0' && input[i] != '\"' && input[i] != '\'')
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
