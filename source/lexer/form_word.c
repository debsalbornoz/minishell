/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:35:20 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/09 18:01:30 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//  int form_word(t_list *list, int signal, char *input, char *temp, int i)
// {
// 	int len;
// 	len = find_len(&input[i], signal);
// 	if(len != 0)
// 	{
// 		temp = ft_calloc((len + 1), sizeof(char));
// 		ft_strlcpy(temp, &input[i], len + 1);
// 		list = add_node(list, temp);
// 	}

// 	return (len);
// }

int form_word(t_list *list, int signal, char *input, int i)
{
    int len;
	char *temp;

    len = find_len(&input[i], signal);
    if (len != 0)
	{
        temp = ft_calloc((len + 1), sizeof(char));
        ft_strlcpy(temp, &input[i], len + 1);
        list = add_node(list, temp);
		free(temp);
    } 
	else
        temp = NULL;

    return len;
}

int find_len(char *input, int signal)
{
	int i = 0;

	if (signal)
	{
		i = 1;
	while (input[i] != '\0' && input[i] != signal)
		i++;
	if (input[i] == signal)
		i++;
    }
	else
	{
		while (input[i] != '\0' && !is_delimiter(input[i]))
			i++;
	}

    return i;
}
