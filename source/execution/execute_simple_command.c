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

int    is_simple_command(t_list *lst_tokens)
{
    lst_tokens->node = lst_tokens->head;
    while(lst_tokens->node)
    {
        if(is_redirect_or_pipe(node->next->data->token->type))
            return(0)
        lst_tokens->node = lst_tokens->node->next;
    }
    return (1);
}

t_list *create_execution_list(t_list *lst_tokens, t_list *lst_execution, t_list *envp)
{
    if(is_simple_command(lst_tokens) &&)
    {
        lst_execution = add_node(lst_execution);
        lst_execution->node->data->execution->simple = 1;
        lst_execution->node->data->execution->command_table = create_command_table(lst_token);
        lst_execution->node->data->execution->envp = list_to_matrix(envp);
    }
}

char    **create_command_table()