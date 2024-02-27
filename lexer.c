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