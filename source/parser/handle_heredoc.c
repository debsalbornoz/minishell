/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:09:07 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/06 21:20:54 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


t_list	*handle_heredoc(t_list *tokens)
{
	t_node	*aux;
	int		i;

	aux = tokens->head;
	i = 0;
	while (aux)
	{
		if (aux->data->token->type == HEREDOC)
		{
			if (aux->next)
			{
				if (open_here_file(aux->next->data->token->value, i) == 0)
				{
					
				}
			}
		}
		if (aux->data->token->type == PIPE)
			i++;
		aux = aux->next;
	}
}

int	open_here_file(char *eof, int i)
{
	char	*filename;
	char	*index;
	int		flag;
	int		fd_stdin;
	int		fd;
	char	*input;

	fd_stdin = dup(STDIN_FILENO);
	index = ft_itoa(i);
	filename = ft_strjoin("/tmp/", index);
	input = NULL;
	free(index);
	flag = 0;
	flag = flag | O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(filename, flag, 0777);
	if (fd == -1)
		return (-1);
	while (1)
	{
		input = readline("> ");
		if (ft_strncmp(input, eof, ft_strlen(input)))
		{
			ft_putstr_fd(input, fd);
			ft_putstr_fd("\n", fd);
			free(input);
		}
		else
		{
			close(fd);
			free(input);
			break;
		}
	}
	return (0);
}
