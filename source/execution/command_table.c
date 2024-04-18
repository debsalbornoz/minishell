/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/06 17:16:04 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char    **create_command_table(t_list *lst_tokens, t_list *lst_execution)
{
    int i;
    char **command_table;
    int nodes;

    i = 0;
    command_table = NULL;
    if(!lst_tokens)
        return (NULL);
    nodes = count_nodes(lst_tokens);
    command_table = ft_calloc(nodes + 1, sizeof(char *));
    if(!command_table)
        return (NULL);
    lst_tokens->node = lst_tokens->head;
    while(lst_tokens && i < nodes)
    {
        command_table[i] = ft_strdup(lst_tokens->node->data->token->value);
        lst_tokens->node = lst_tokens->node->next;
        i++;
    }
    command_table[i] = NULL;
    if(lst_execution)
        lst_execution->node->data->execution->command_table = command_table;
    return(command_table);
}