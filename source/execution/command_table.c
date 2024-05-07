/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/07 19:16:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**create_command_table(t_list *tokens, t_list *exec)
{
	int		i;
	char	**command_table;
	int		nodes;
	t_node	*aux;

	i = 0;
	command_table = NULL;
	if (!tokens)
		return (NULL);
	nodes = count_nodes(tokens);
	command_table = ft_calloc(nodes + 1, sizeof(char *));
	if (!command_table)
		return (NULL);
	aux = tokens->head;
	while (tokens && i < nodes)
	{
		command_table[i] = ft_strdup(aux->data->token->value);
		aux = aux->next;
		i++;
	}
	command_table[i] = NULL;
	if (exec)
		exec->node->data->execution->command_table = command_table;
	return (command_table);
}
