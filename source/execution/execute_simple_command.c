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

t_list *create_execution_list(t_list *lst_tokens, t_list *lst_exec, t_list *lst_env)
{
    if (is_simple_command(lst_tokens))
    {
        lst_exec = add_node(lst_exec);
        lst_exec->node->data = ft_calloc(1, sizeof(union u_data));
        if(!lst_exec->node->data)
            return (NULL);
		lst_exec->node->data->execution = ft_calloc(1, sizeof(t_exec));
        if (!lst_exec->node->data->execution)
            return (NULL);
        lst_exec->node->data->execution->envp = env_list_to_str_array(lst_env);
        lst_exec->node->data->execution->command_table = create_command_table(lst_tokens, lst_exec);
        lst_exec->node->data->execution->path = save_path(lst_exec,lst_tokens, lst_env);
    }
    lst_exec->node = lst_exec->head;
    return (lst_exec);
}
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

char	**env_list_to_str_array(t_list *lst_env)
{
	char	**envp;
	int		i;

	if (!lst_env)
		return (NULL);
	i = 0;
	lst_env->node = lst_env->head;
	envp = ft_calloc((count_nodes(lst_env) + 1), sizeof(char *));
	if (!envp)
		return (NULL);
	while (lst_env->node)
	{
		envp[i] = concatenate(lst_env->node->data->env->name,
				lst_env->node->data->env->value);
		i++;
		lst_env->node = lst_env->node->next;
	}
	envp[i] = NULL;
	lst_env->node = lst_env->head;
	return (envp);
}

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
char  *save_path(t_list *lst_exec, t_list *lst_token, t_list *lst_env)
{
    int i;
    char *path;
    char **path_array;
    int validate;

    i = -1;
    path_array = split_path(lst_env);
    while(path_array[i++] != NULL)
    {
        path = create_path(path_array[i],lst_token);
        validate = validate_path(lst_exec, path, lst_env);
        free(path);
        if (validate)
        {
            free_path(path_array);
           return (path);
        }
    }
    if (!validate)
    {
        update_env_list(lst_env, "?", " 127: command not found");
        printf("%s\n", "comando nao encontrado");
    }
    free_path(path_array);
    return (path);
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