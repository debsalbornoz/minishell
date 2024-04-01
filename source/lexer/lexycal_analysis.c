/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexycal_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 20:05:01 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/01 20:05:03 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

t_list	*lexical_analysis(char *input, t_list *lst_tokens)
{
	lst_tokens = tokenization(lst_tokens, input);
	lst_tokens = type_assignment(lst_tokens);
	runs_on_list(lst_tokens, print_lst_tokens);
	lst_tokens->node = lst_tokens->head;
	return (lst_tokens);
}
