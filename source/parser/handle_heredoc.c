/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:09:07 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/08 17:36:40 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list *handle_heredoc(t_list *tokens)
{
	t_node *aux;
	char	*filename;

	aux = tokens->head;
	int i = 0;
	filename = NULL;
	while (aux)
	{
		if (aux->data->token->type == HEREDOC && aux->next)
		{
			filename = open_here_file(aux->next->data->token->value, i);
			if (!filename)
				return NULL;
			aux->next->data->token->value = filename;
		}
		if (aux->data->token->type == PIPE)
			i++;
		aux = aux->next;
	}
	return (tokens);
}

char *open_here_file(char *eof, int i)
{
	char	*filename;
	int		flag;
	int		fd;
	char	*new_eof;

	filename = get_filename(i);
	if (!filename)
		return (NULL);
	flag = 0;
	flag = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(filename, flag, 0777);
	if (fd == -1)
	{
		free(filename);
		return NULL;
	}
	new_eof = handle_quotes(eof, fd, filename);
	open_heredoc_prompt(new_eof, fd);
	close(fd);
	free(new_eof);
	return filename;
}
int open_heredoc_prompt(char *new_eof, int fd)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (ft_strncmp(input, new_eof, ft_strlen(input)) == 0)
		{
			free(input);
			break;
		}
		ft_putstr_fd(input, fd);
		ft_putstr_fd("\n", fd);
		free(input);
	}
	return (0);
}
