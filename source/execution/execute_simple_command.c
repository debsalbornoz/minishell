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
        if(is_redirect_or_pipe(lst_tokens->node->data->token->type))
            return(0);
        lst_tokens->node = lst_tokens->node->next;
    }
    lst_tokens->node = lst_tokens->head;
    return (1);
}

t_list *create_execution_list(t_list *lst_tokens, t_list *lst_exec, t_list *envp)
{
    char    **matrix;
    char    **command_table;

    if(is_simple_command(lst_tokens))
    {
        lst_exec = add_node(lst_exec);
        lst_exec->node->data = ft_calloc(1, sizeof(union u_data));
		lst_exec->node->data->execution = ft_calloc(1, sizeof(t_exec));
        matrix = list_to_matrix(envp, 0 , 0);
        lst_exec->node->data->execution->envp = matrix;
        command_table = create_command_table(lst_tokens, lst_exec);
        lst_exec->node->data->execution->command_table = command_table;
        save_path(lst_exec,lst_tokens, envp);

    }
    lst_exec->node = lst_exec->head;
    return (lst_exec);
}

char    **create_command_table(t_list *lst_tokens, t_list *lst_execution)
{
    int i;
    char **command_table;
    int nodes;

    i = 0;
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

char **duplicate_matrix(char **matrix)
{
    int i;
    char **temp;
    int     len;


    i = 0;
    len = 0;
    while(matrix[i] != NULL)
        i++;
    temp = ft_calloc((i + 1), sizeof(char *));
    i = 0;
    while(matrix[i] != NULL)
    {
        len = ft_strlen(matrix[i]);
        temp[i] = ft_calloc(len + 1, sizeof(char ));
        ft_strlcpy(temp[i], matrix[i], ft_strlen(matrix[i]));
        i++;
    }
    return(temp);
}

void print_matrix(char **matrix)
{
    int i;
    i = 0;
    while(matrix[i] != NULL)
    {
        printf("%s\n", matrix[i]);
        i++;
    }
}