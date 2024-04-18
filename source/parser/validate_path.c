#include "../../include/minishell.h"

int    validate_path(t_list *lst_exec, char *path)
{
        if(access(path, X_OK) == 0)
        {
            if (lst_exec)
            {
            lst_exec->node->data->execution->path = path;
            printf("%s\n",lst_exec->node->data->execution->path);
            return (1);
            }
        }
    return (0);
}

char *create_path(char *path, t_list *lst_token)
{
    char *temp;
    
    temp = NULL;
    if(!lst_token)
        return (NULL);
    lst_token->node = lst_token->head;
    while (lst_token->node)
    {
        if (lst_token->node->data->token->type == COMMAND)
        {
            temp = concatenate_path(path, lst_token->node->data->token->value);
            return (temp);
        }
        lst_token->node = lst_token->node->next;
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
    if (!s1 || !s2)
        return (NULL);
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


