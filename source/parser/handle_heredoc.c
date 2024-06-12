/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:09:07 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/11 21:46:37 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

int		check_signals(char *input, char *filename, int fd_in, char *env);

t_list	*process_heredoc_tokens(t_list *tokens)
{
	t_node	*aux;
	char	*filename;
	int		i;

	i = 0;
	aux = tokens->head;
	filename = NULL;
	while (aux)
	{
		if (aux->data->token->type == HEREDOC && aux->next)
		{
			filename = get_filename(i);
			if (!handle_heredoc(aux, aux->next->data->token->value, filename))
			{
				free_list(tokens, free_lst_tokens);
				return (NULL);
			}
		}
		if (aux->data->token->type == PIPE)
			i++;
		aux = aux->next;
	}
	return (tokens);
}

char	*handle_heredoc(t_node *token, char *eof, char *filename)
{
	int		flag;
	int		fd;
	char	*new_eof;

	if (!filename)
		return (NULL);
	flag = 0;
	fd = open_here_file(filename);
	if (is_quoted(eof))
	{
		new_eof = remove_eof_quotes(eof);
		free(eof);
		eof = new_eof;
		flag = 1;
	}
	while (1)
	{
		if (!open_prompt(eof, flag, fd, filename))
			return (NULL);
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
	char	*env;
	int		fd_in;

	handle_heredoc_signals();
	fd_in = dup(STDIN_FILENO);
	(void)flag;
	input = readline("> ");
	env = ft_get_env("?");
	if (check_signals(input, filename, fd_in, env))
		return (0);
	else if (ft_strncmp(input, eof, ft_strlen(input)))
	{
		ft_putstr_fd(input, fd);
		ft_putstr_fd("\n", fd);
		free(input);
	}
	else
	{
		close(fd);
		free(input);
		return (0);
	}
	return (1);
}

int	check_signals(char *input, char *filename, int fd_in, char *env)
{
	t_list	*envp;

	envp = data_env_addr();
	envp->node = envp->head;
	if (!ft_strncmp(env, "130", 3))
	{
		unlink(filename);
		dup2(fd_in, 0);
		printf("\n");
		return (1);
	}
	else if (!input)
	{
		printf("warning:here-document delimited by end-of-file(wanted `eof')\n");
		update_env_list(envp, "?", "131");
		return (1);
	}
	else
		return (0);
}
