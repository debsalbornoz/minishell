/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:21:25 by dlamark-          #+#    #+#             */
/*   Updated: 2024/02/20 18:18:41 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void tokenize_input(t_tokens **list, char *str)
{
    int i;
	int len;
	int j;

	i = 0;

	while (str[i] != '\0')
	{
		j = 0;
        while (str[i] == 32 || str[i] == '\t')
            i++;
        if (str[i] == '|')
            add_pipe(list, str);
        else if ((str[i] == '>' && str[i + 1] != '>') || (str[i] == '<' && str[i + 1] != '<'))
            add_redirect(list, str, str[i]);
		else if((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
		{
			add_multi_redirect(list,str, str[i]);
			i++;
		}
		else
		{
			len = find_len(str + i);
			add_word(list,str, str + i, len);
			while(j++ < len)
			{
				if(j == len)
					break;
				i++;
			}
			
		}
        i++;
    }
}

int	find_len(char *str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		if(str[i] == 32 || str[i] == '\t' || str[i] == '>' || str[i] == '|' || str[i] == '<')
		{
			break;
		}
		i++;
	}
	return(i);
}
void add_pipe(t_tokens **list, char *str) {
    t_tokens *new_node = append_node(list, str);
    new_node->type = "pipe";
	new_node->option = "none";
    new_node->value = "|";
}

void add_redirect(t_tokens **list, char *str, char c) {
    t_tokens *new_node = append_node(list, str);
	if(c == '>')
	{
		new_node->type = "redirect";
    	new_node->option = "output_redirect";
    	new_node->value = ">";
	}
	else if (c == '<')
	{
		new_node->type = "redirect";
    	new_node->option = "input_redirect";
    	new_node->value = "<";
	}

}

void add_multi_redirect(t_tokens **list, char *str, char c)
{
    t_tokens *new_node = append_node(list, str);
	if(c == '>')
	{
		new_node->type = "redirect";
    	new_node->option = "append_redirect";
    	new_node->value = ">>";
	}
	else if (c == '<')
	{
		new_node->type = "redirect";
    	new_node->option = "heredoc";
    	new_node->value = "<<";
	}
}
char 	*ft_strcpy(char *dst, const char *src, int size)
{
	int	i;

	i = 0;

	if (dst == NULL || src == NULL)
		return (NULL);
	else if (size == 0)
		return (NULL);
	while (i < size && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	add_word(t_tokens **list, char *str, char *s, int len)
{
	t_tokens *new_node;
	char *temp;

	temp = NULL;
	new_node = append_node(list, str);
	temp = ft_calloc((len + 1),sizeof(char));
	temp = ft_strcpy(temp,s,len);
	new_node->type = "word";
    new_node->option = "none";
    new_node->value = temp;
}