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


char *save_path(t_list *lst_exec, t_list *lst_token, t_list *lst_env)
{
    int i;
    char *path;
    char **path_array;
    int validate;

    i = 0;
    if (!lst_exec || !lst_token || !lst_env)
        return NULL;

    path_array = split_path(lst_env);
    if (!path_array)
        return NULL;
    while (path_array[i] != NULL)
    {
        path = create_path(path_array[i], lst_token);
        validate = validate_path(lst_exec, path);
        if (validate)
        {
            free_path(path_array);
            return path;
        }
        free(path);
        i++;
    }
    free_path(path_array);
    update_env_list(lst_env, "?", " 127: command not found");
    printf("%s\n", "comando nao encontrado");

    return NULL;
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