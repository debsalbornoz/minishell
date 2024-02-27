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

void init_tokenization(t_tokens **list, char *str) {
    int i = 0;
    while (str[i] != '\0')
	{
        while (str[i] == 32 || str[i] == '\t')
            i++;
        if (str[i] == '|')
            add_pipe(list, str);
        else if (str[i] == '>' && str[i + 1] != '>')
            add_output_redirect(list, str);
        else if(str[i] == '<' && str[i + 1] != '<')
			add_input_redirect(list,str);
		else if(str[i] == '>' && str[i + 1] == '>')
		{
			add_append_redirect(list,str);
			i++;
		}
		else if(str[i] == '<' && str[i + 1] == '<')
		{
			add_heredoc(list,str);
			i++;
		}
        i++;
    }
}

void add_pipe(t_tokens **list, char *str) {
    t_tokens *new_node = append_node(list, str);
    new_node->type = "pipe";
	new_node->option = "none";
    new_node->value = "|";
}

void add_output_redirect(t_tokens **list, char *str) {
    t_tokens *new_node = append_node(list, str);
    new_node->type = "redirect";
    new_node->option = "output_redirect";
    new_node->value = ">";
}

void add_input_redirect(t_tokens **list, char *str) {
    t_tokens *new_node = append_node(list, str);
    new_node->type = "redirect";
    new_node->option = "input_redirect";
    new_node->value = "<";
}

void add_append_redirect(t_tokens **list, char *str) {
    t_tokens *new_node = append_node(list, str);
    new_node->type = "redirect";
    new_node->option = "append_redirect";
    new_node->value = ">>";
}

void add_heredoc(t_tokens **list, char *str) {
    t_tokens *new_node = append_node(list, str);
    new_node->type = "redirect";
    new_node->option = "heredoc";
    new_node->value = "<<";
}
/*int	find_redirect(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' || (str[i] == '>' && str[i + 1] == '>'))
			return (1);
		else if (str[i] == '<' || (str[i] == '<' && str[i + 1] == '<'))
			return (1);
		i++;
	}
	return (0);
}

void	add_redirect(t_tokens **list, char *str)
{
	int	i;

	i = 0;
	(*list)->type = "redirect";
	while (str[i] != '\0')
	{
		if (str[i] == '>' && str[i + 1] != '\0' && str[i + 1] != '>')
		{
			(*list)->option = "output_redirection";
		}
		if (str[i] == '<' && str[i + 1] != '\0' && str[i + 1] != '<')
		{
			append_node(list, str);
			(*list)->option = "input_redirection";
		}
		if (str[i] == '>' && str[i + 1] != '\0' && str[i + 1] == '>')
		{
			append_node(list, str);
			(*list)->option = "append_output";
		}
		if (str[i] == '<' && str[i + 1] != '\0' && str[i + 1] == '<')
		{
			append_node(list, str);
			(*list)->option = "heredoc";
		}
		i++;
	}
}
*/