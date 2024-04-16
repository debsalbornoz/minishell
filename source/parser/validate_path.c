#include "../../include/minishell.h"

int    validate_path(t_list *lst_exec, char *path, t_list *lst_env)
{
    int i;
    (void) lst_env;
    i = 0;
        if(access(path, X_OK) == 0)
        {
            lst_exec->node->data->execution->path = ft_strdup(path);
            return (1);
        }
        i++;
    return (0);
}

char *create_path(char *path, t_list *lst_token)
{
    char *temp;
    
    lst_token->node = lst_token->head;
    while (lst_token->node)
    {
        if (lst_token->node->data->token->type == COMMAND)
            temp = concatenate_path(path, lst_token->node->data->token->value);
        lst_token->node = lst_token->node->next;
    }
    return (temp);
}


char *concatenate_path(char *s1, char *s2)
{
    int i;
    int j;
    int len;
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
    i = 0;
    path_array = split_path(lst_env);

    while(path_array[i] != NULL)
    {
        path = create_path(path_array[i],lst_token);
        printf("%s\n", path);
        //if (validate_path(lst_exec, path, lst_env))
        //   return (1);
        i++;
    }
    return (0);
}