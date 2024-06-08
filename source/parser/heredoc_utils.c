/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:12:44 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/08 17:29:21 by dlamark-         ###   ########.fr       */
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
	if (counter > 0)
	{
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
	}
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

char	*get_filename(int i)
{
	char *filename;
	char *index;

	index = ft_itoa(i);
	if (!index)
		return (NULL);
	filename = ft_strjoin("/tmp/", index);
	if (!filename)
		return (NULL);
	free(index);
	return (filename);
}
char	*handle_quotes(char *eof, int fd, char *filename)
{
	char *new_eof;

	new_eof = NULL;
	if (is_quoted(eof))
	{
		new_eof = remove_eof_quotes(eof);
		free(eof);
	}
	else
	{
		new_eof = ft_strdup(eof);
		free(eof);
	}
	if (!new_eof)
	{
		close(fd);
		free(filename);
		return (NULL);
	}
	return (new_eof);
}
