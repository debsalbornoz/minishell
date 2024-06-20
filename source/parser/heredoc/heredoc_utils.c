/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:55:37 by codespace         #+#    #+#             */
/*   Updated: 2024/06/20 18:26:18 by codespace        ###   ########.fr       */
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

char	*remove_eof_quotes(char *eof)
{
	int		counter;
	char	*new_eof;

	new_eof = NULL;
	counter = find_new_len(eof, ft_strlen(eof), 0, 0);
	if (counter <= 0)
		return (NULL);
	new_eof = ft_calloc((counter + 1), sizeof(char));
	new_eof = unquote_str(eof, new_eof, 0, 0);
	free (eof);
	return (new_eof);
}

/*int	new_eof_size(char *eof)
{
	int		i;
	int		counter;
	char	quotes;
	int		signal;

	i = 0;
	counter = 0;
	signal = 0;
	quotes = 0;
	while (eof[i])
	{
		if (eof[i] != '\'' || eof[i] != '\"')
			counter++;
		i++;
	}
	return (counter);
}
*/
