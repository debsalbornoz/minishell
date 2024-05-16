/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:07:45 by codespace         #+#    #+#             */
/*   Updated: 2024/05/16 14:06:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*handle_redirect(t_list *tokens)
{
	tokens = open_file(tokens);
	//tokens = remove_redirect_and_file(tokens);
	tokens->node = tokens->head;
	return (tokens);
}

t_list	*open_file(t_list *tokens)
{
	t_node	*aux;
	int		fd;

	aux = tokens->head;
	while (aux)
	{
		if (find_redirect(aux->data->token->type))
		{
			if (aux->next)
			{
				fd = open(aux->next->data->token->value, set_flag(aux), 0644);
				if (fd == -1)
					return (NULL);
				if (aux->data->token->type == OUTPUT
					|| aux->data->token->type == APPEND)
					fd = dup2(fd, 1);
				else if (aux->data->token->type == INPUT
					|| aux->data->token->type == HEREDOC)
					fd = dup2(fd, 0);
			}
		}
		aux = aux->next;
	}
	return (tokens);
}

int	set_flag(t_node *node)
{
	int	flag;

	flag = 0;
	if (node->data->token->type == OUTPUT)
		flag = flag | O_WRONLY | O_CREAT | O_TRUNC;
	if (node->data->token->type == APPEND)
		flag = flag | O_WRONLY | O_CREAT | O_APPEND;
	if (node->data->token->type == HEREDOC || node->data->token->type == INPUT)
		flag = flag | O_RDONLY;
	return (flag);
}

void	close_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

void	free_token(t_node *node)
{
	free(node->data->token->value);
	free(node->data->token);
	free(node->data);
	free(node);
}
