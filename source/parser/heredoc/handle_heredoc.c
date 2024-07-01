/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:09:07 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/01 11:42:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
					filename) || !filename)
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

char	*get_filename(int i)
{
	char	*filename;
	char	*index;

	filename = NULL;
	index = ft_itoa(i);
	filename = ft_strjoin("/tmp/", index);
	free(index);
	return (filename);
}

char	*handle_heredoc(t_node *token, char *eof, char *filename)
{
	int		expand;
	int		fd;
	int		flag;

	expand = 0;
	fd = setup_heredoc_env(filename);
	if (is_quoted(eof))
	{
		eof = remove_eof_quotes(eof);
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
	free (eof);
	close(fd);
	token->next->data->token->value = filename;
	return (filename);
}

int	setup_heredoc_env(char *filename)
{
	t_list	*envp;
	int		fd;

	envp = data_env_addr();
	update_env_list(envp, "?", "0");
	fd = open_here_file(filename);
	handle_heredoc_signals();
	return (fd);
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

