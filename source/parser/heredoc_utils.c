/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:55:37 by codespace         #+#    #+#             */
/*   Updated: 2024/06/11 23:37:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int is_quoted(char *eof)
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
	int		i;
	int		j;

	counter = new_eof_size(eof);
	new_eof = NULL;
	i = 0;
	j = 0;
	if (counter <= 0)
		return (NULL);
	new_eof = ft_calloc((counter + 1), sizeof(char ));
	while (eof[i])
	{
		if (eof[i] != '\'' && eof[i] != '\"')
		{
			new_eof[j] = eof[i];
			j++;
		}
		i++;
	}
	new_eof[j] = '\0';
	return (new_eof);
}

int new_eof_size(char *eof)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (eof[i] != '\0')
	{
		if(eof[i] != '\'' && eof[i] != '\"')
			counter++;
		i++;
	}
	return (counter);
}
char *get_filename(int i)
{
	char	*filename;
	char	*index;

	filename = NULL;
	index = ft_itoa(i);
	filename = ft_strjoin("/tmp/", index);
	free(index);
	return (filename);
}
