/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/29 12:18:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**create_command_table(t_list *lst_tokens, t_list *lst_execution)
{
	int		i;
	char	**command_table;
	int		nodes;
	t_node	*aux;

	i = 0;
	command_table = NULL;
	if (!lst_tokens)
		return (NULL);
	nodes = count_nodes(lst_tokens);
	command_table = ft_calloc(nodes + 1, sizeof(char *));
	if (!command_table)
		return (NULL);
	aux = lst_tokens->head;
	while (lst_tokens && i < nodes)
	{
		command_table[i] = ft_strdup(aux->data->token->value);
		aux = aux->next;
		i++;
	}
	command_table[i] = NULL;
	if (lst_execution)
		lst_execution->node->data->execution->command_table = command_table;
	return (command_table);
}
