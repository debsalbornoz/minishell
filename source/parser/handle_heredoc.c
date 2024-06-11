/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:09:07 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/11 23:36:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*process_heredoc_tokens(t_list *tokens, t_list *envp)
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
				filename = get_filename(i);
				if (!handle_heredoc(aux, aux->next->data->token->value, filename, envp))
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

char 	*handle_heredoc(t_node *token, char *eof, char *filename, t_list *envp)
{
	int		flag;
	int		fd;
	char	*new_eof;

	filename = get_filename(i);
	if (!filename)
		return (NULL);
	flag = 0;
	fd = open_here_file(filename);
	if (is_quoted(eof))
	{
		new_eof = remove_eof_quotes(eof);;
		free(eof);
		eof = new_eof;
		flag = 1;
	}
	while (1)
	{
		if (!open_prompt(eof, flag, fd, envp, filename))
			return (NULL);
	}
	free(token->next->data->token->value);
	token->next->data->token->value = filename;
	return (filename);
}
int open_here_file(char *filename)
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

int	open_prompt(char *eof, int flag, int fd, t_list *envp, char *filename)
{
	char	*input;
	char	*env;

	envp->node = envp->head;
	handle_heredoc_signals();
	(void)flag;
	input = readline("> ");
	env = ft_get_env(envp, "?");
	if (!ft_strncmp(env, "130", 3))
	{
		unlink(filename);
		printf("\n");
		return (0);
	}
	else if (!input)
	{
		printf("bash: warning: here-document delimited by end-of-file (wanted `eof')\n");
		update_env_list(envp, "?", "131");
		return (0);
	}
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
		return(0);
	}
	return (1);
}

