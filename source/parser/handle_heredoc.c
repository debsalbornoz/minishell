/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:09:07 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/12 21:56:31 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		check_signals(char *input, char *filename, int fd_in);
void	write_in_file(char *input, int fd, int flag);

t_list	*process_heredoc_tokens(t_list *tokens)
{
	t_node	*token;
	char	*filename;
	int		i;

	i = 0;
	token = tokens->head;
	filename = NULL;
	while (token)
	{
		if (token->data->token->type == HEREDOC && token->next)
		{
			filename = get_filename(i);
			if (!handle_heredoc(token, token->next->data->token->value,
					filename))
			{
				free_list(tokens, free_lst_tokens);
				return (NULL);
			}
		}
		if (token->data->token->type == PIPE)
			i++;
		token = token->next;
	}
	return (tokens);
}

char	*handle_heredoc(t_node *token, char *eof, char *filename)
{
	int		expand;
	int		fd;
	char	*new_eof;
	int		flag;
	t_list	*envp;

	if (!filename)
		return (NULL);
	envp = data_env_addr();
	expand = 0;
	update_env_list(envp, "?", "0");
	fd = open_here_file(filename);
	handle_heredoc_signals();
	if (is_quoted(eof))
	{
		new_eof = remove_eof_quotes(eof);
		free(eof);
		eof = new_eof;
		expand = 1;
	}
	while (1)
	{
		flag = open_prompt(eof, expand, fd, filename);
		if (flag < 0)
			return (NULL);
		if (flag == 2 || flag == 1)
			break ;
	}
	free(token->next->data->token->value);
	token->next->data->token->value = filename;
	return (filename);
}

int	open_here_file(char *filename)
{
	int	flag;
	int	fd;

	flag = 0;
	flag = flag | O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(filename, flag, 0777);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	open_prompt(char *eof, int flag, int fd, char *filename)
{
	char	*input;
	int		fd_stdin;
	int		result;
	t_list	*envp;

	result = 0;
	fd_stdin = dup(STDIN_FILENO);
	envp = data_env_addr();
	input = readline("> ");
	result = check_signals(input, filename, fd_stdin);
	if (input && ft_strncmp(input, eof, ft_strlen(input)))
	{
		write_in_file(input, fd, flag);
		result = 3;
	}
	else if (result == 0)
	{
		close(fd);
		free(input);
		result = 2;
	}
	return (result);
}

void	write_in_file(char *input, int fd, int flag)
{
	(void)flag;
	ft_putstr_fd(input, fd);
	ft_putstr_fd("\n", fd);
	free(input);
}
