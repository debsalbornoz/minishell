#include "../../include/minishell.h"

int    validate_path(t_list *lst_exec, char *path, t_list *lst_env)
{
    (void) lst_env;
        if(access(path, X_OK) == 0)
        {
            lst_exec->node->data->execution->path = ft_strdup(path);
            printf("%s\n", path);
            return (1);
        }
    return (0);
}

char *create_path(char *path, t_list *lst_token)
{
    char *temp;
    
    temp = NULL;
    lst_token->node = lst_token->head;
    while (lst_token->node)
    {
        if (lst_token->node->data->token->type == COMMAND)
        {
            temp = concatenate_path(path, lst_token->node->data->token->value);
            lst_token->node = lst_token->node->next;
            return (temp);
        }
    }
    return (temp);
}


char *concatenate_path(char *s1, char *s2)
{
    int i;
    int j;
    int len;
    i = 0;
    j = 0;
    len = ft_strlen(s1) + ft_strlen(s2) + 2;
    char *temp;

    temp = ft_calloc(len, sizeof(char));
    while (s1[i] != '\0')
    {
        temp[i] = s1[i];
        i++;
    }
    temp[i] = '/';
    i++;
    while(s2[j] != '\0')
    {
        temp[i] = s2[j];
        i++;
        j++;
    }
    return (temp);
}

int save_path(t_list *lst_exec, t_list *lst_token, t_list *lst_env)
{
    int i;
    char *path;
    char **path_array;
    (void) lst_token;
    (void)lst_exec;
    int validate;

    i = 0;
    path_array = split_path(lst_env);

    while(path_array[i] != NULL)
    {
        path = create_path(path_array[i],lst_token);
        validate = validate_path(lst_exec, path, lst_env);
        if (validate)
        {
            free_path(path_array);
           return (1);
        }
        i++;
    }
    if (!validate)
    {
        update_env_list(lst_env, "?", " 127: command not found");
        printf("%s\n", "comando nao encontrado");
    }
    free_path(path_array);
    return (0);
}