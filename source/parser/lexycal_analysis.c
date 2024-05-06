/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexycal_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 20:05:01 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/06 14:18:35 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*lexical_analysis(char *input, t_list *lst_tokens)
{
	if (!lst_tokens)
		return (NULL);
	lst_tokens = lexer(lst_tokens, input);
	lst_tokens = type_assignment(lst_tokens);
	lst_tokens->node = lst_tokens->head;
	return (lst_tokens);
}

int	check_input(char *input)
{
	if (!input || !is_closed(input))
	{
		printf("\n");
		return (0);
	}
	if (!*input)
		return (1);
	return (2);
}
