/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:09:07 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/07 16:42:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int is_quoted(char *eof);
int new_eof_size(char *eof);
char	*remove_eof_quotes(char *eof);
int is_quoted(char *eof);
char 	*open_here_file(char *eof, int i);

t_list	*handle_heredoc(t_list *tokens)
{
	t_node	*aux;
	int		i;
	char	*filename;


	aux = tokens->head;
	i = 0;
	filename = NULL;
	while (aux)
	{
		if (aux->data->token->type == HEREDOC)
		{
			if (aux->next)
			{
				filename = open_here_file(aux->next->data->token->value, i);
				if (filename)
				{
					free(aux->next->data->token->value);
					aux->next->data->token->value = filename;
				}
				else
					return (NULL);
			}
		}
		if (aux->data->token->type == PIPE)
			i++;
		aux = aux->next;
	}
	return (tokens);
}

char 	*open_here_file(char *eof, int i)
{
	char	*filename;
	char	*index;
	int		flag;
	int		fd_stdin;
	int		fd;
	char	*input;
	char	*new_eof;

	flag = 0;
	if (is_quoted(eof))
	{
		new_eof = remove_eof_quotes(eof);
		printf("new eof: %s \n", new_eof);
		free(eof);
		eof = new_eof;
		printf("%s\n", eof);
		flag = 1;
	}
	(void)fd_stdin;
	fd_stdin = dup(STDIN_FILENO);
	index = ft_itoa(i);
	filename = ft_strjoin("/tmp/", index);
	input = NULL;
	free(index);
	flag = 0;
	flag = flag | O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(filename, flag, 0777);
	if (fd == -1)
		return (NULL);
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
	return (filename);
}

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
		new_eof = ft_calloc((counter + 1), sizeof(char ));
	while (eof[i])
	{
		if (eof[i] != '\'' || eof[i] != '\"')
		{
			new_eof[j] = eof[i];
			j++;
		}
		i++;
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
