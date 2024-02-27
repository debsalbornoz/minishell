#include "minishell.h"


t_tokens    *create_node(char *str)
{
    t_tokens    *new_node;

    new_node = (t_tokens *)ft_calloc(1, sizeof(t_tokens));
    new_node->str = str;
    new_node->builtin = 0;
    new_node->enabled = 0;
    new_node->type = NULL;
    new_node->option = NULL;
    new_node->value = NULL;
    new_node->prev = NULL;
    new_node->next = NULL;   
    return(new_node); 
}

t_tokens *append_node(t_tokens **list, char *str)
{
    t_tokens *new_node = create_node(str);

    new_node->next = NULL;

    if (*list == NULL) {
        new_node->prev = NULL;
        *list = new_node;
    } else {
        t_tokens *current_node = *list;
        while (current_node->next != NULL) {
            current_node = current_node->next;
        }

        current_node->next = new_node;
        new_node->prev = current_node;
    }

    return new_node;
}