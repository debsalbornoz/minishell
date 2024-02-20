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

void	init_tokenization(t_tokens **list, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == 32 || str[i] == '\t')
			i++;
		if (str[i] == '|')
		{
			add_node(list, str);
			(*list)->type = "pipe";
		}
		else if (find_redirect(str + i))
		{
			add_node(list, str);
			add_redirect(list, str + i);
		}
		i++;
	}
}

int	find_redirect(char *str)
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
			add_node(list, str);
			(*list)->option = "input_redirection";
		}
		if (str[i] == '>' && str[i + 1] != '\0' && str[i + 1] == '>')
		{
			add_node(list, str);
			(*list)->option = "append_output";
		}
		if (str[i] == '<' && str[i + 1] != '\0' && str[i + 1] == '<')
		{
			add_node(list, str);
			(*list)->option = "heredoc";
		}
		i++;
	}
}
