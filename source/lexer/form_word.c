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

char	*ft_strjoinchr(char *str, char chr)
{
	char	*temp_s1;
	char	*temp_s2;
	char	*res;

	temp_s1 = 0;
	temp_s2 = 0;
	res = 0;
	temp_s2 = ft_calloc(2, sizeof(char));
	*temp_s2 = chr;
	if (!str)
	{
		res = ft_strdup(temp_s2);
		free(temp_s2);
		return (res);
	}
	temp_s1 = ft_strdup(str);
	res = ft_strjoin(temp_s1, temp_s2);
	free(temp_s1);
	free(temp_s2);
	return (res);
}

// char	*form_word(t_list *list, int signal, char *input, char **temp, int i)
// {
// 	if ((temp && !input[i + 1])
// 		|| (temp && !signal && is_delimiter(input[i])))
// 	{
// 		list = add_node(list, *temp);
// 		temp = 0;
// 	}
// 	return (*temp);
// }

 int form_word(t_list *list, int signal, char *input, char *temp, int i)
{
	int len;
	len = find_len(&input[i], signal);
	if(len != 0)
	{
		temp = ft_calloc((len + 1), sizeof(char));
		ft_strlcpy(temp, &input[i], len + 1);
		list = add_node(list, temp);
		// free(temp);
	}

	return (len);
}



// int  find_len(char *input, int signal)
// {
// 	int i;

// 	i = 0;
	
// 	if(signal)
// 	{
// 		i = 1;
// 		while(input[i] != '\0' && input[i] != signal)
// 			i++;
// 	}
// 	if(input[i] == signal)
// 		i++;
// 	else
// 	while(input[i] != '\0')
// 	{
// 		if(is_delimiter(input[i]))
// 			break;
// 		i++;
// 	}
// 	return(i);
// }

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
