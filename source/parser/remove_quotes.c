/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 20:07:44 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/01 20:07:48 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int find_new_len(t_node *node) {
    char *str;
    int counter;
    char signal;
    int  i;
    int  inside_quotes;

    str = node->data->token->value;
    counter = 0;
    signal = '\0';
    i = 0;
    inside_quotes = 0;
    while (str[i] != '\0')
    {
        if (is_quote(str[i]))
        {
            signal = str[i];
            inside_quotes = 1;
            i++;
        }
        while(inside_quotes && str[i] != signal && str[i] != '\0')
        {
            i++;
            counter++;
        }
        if(str[i] == signal)
        {
            signal = '\0';
            inside_quotes = 0;
            i++;
        }
        if(!signal && !inside_quotes && str[i] != '\0')
        {
            counter++;
            i++;
        }
    }
    return counter;
}
