/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:07:45 by codespace         #+#    #+#             */
/*   Updated: 2024/04/30 12:21:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int set_flag(t_node *node)
{
	int flag;

	flag = 0;
	if (node->data->token->type == OUTPUT)
		flag = flag | O_WRONLY | O_CREAT | O_TRUNC;
	if (node->data->token->type == APPEND)
		flag = flag | O_WRONLY | O_CREAT | O_APPEND;
	if (node->data->token->type == HEREDOC || node->data->token->type == INPUT)
		flag = flag | O_RDONLY;
	return (flag);
}

t_list  *open_file(t_list *lst_tokens)
{
	t_node 	*aux;
	int		fd;

	aux = lst_tokens->head;
	fd = 0;
	while (aux)
	{
		if(find_redirect(aux->data->token->type))
		{
			if (aux->next)
			{
				fd = open(aux->next->data->token->value, set_flag(aux), 0644);
				if (fd == -1)
					return (NULL);
				if (aux->data->token->type == OUTPUT || APPEND)
					fd = dup2(fd, 1);
				if ((aux->data->token->type == INPUT || HEREDOC))
					fd =dup2(fd, 0);
			}
		}
		aux = aux->next;
	}

	return (lst_tokens);
}
t_list *handle_redirect(t_list *lst_tokens, t_list *lst_exec)
{

	(void)lst_exec;
	lst_tokens = open_file(lst_tokens);
	lst_tokens = remove_redirect_and_next(lst_tokens);
	lst_tokens->node = lst_tokens->head;
	return (lst_tokens);
}

t_list *remove_redirect_and_next(t_list *lst_tokens) {
    t_node *current = lst_tokens->head;
    t_node *next_node = NULL;
    t_node *prev_node = NULL;

    if (!lst_tokens || !lst_tokens->head)
        return lst_tokens;

    while (current && current->next) {
        if (find_redirect(current->data->token->type)) {
            next_node = current->next;
            if (prev_node) {
                prev_node->next = next_node->next;
                free(current);
                free(next_node);
                current = prev_node->next;
            } else {
                lst_tokens->head = next_node->next;
                free(current);
                free(next_node);
                current = lst_tokens->head;
            }
        } else {
            prev_node = current;
            current = current->next;
        }
    }

    lst_tokens->node = lst_tokens->head;
    return lst_tokens;
}



