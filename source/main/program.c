/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:46:23 by jraupp            #+#    #+#             */
/*   Updated: 2024/04/29 16:54:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	program(t_list *lst_env)
{
	t_list		lst_tokens;
	char		*input;
	t_list		exec_list;

	lst_tokens.node = 0;
	exec_list.node = 0;
	input = readline("¯\\_(ツ)_/¯: ");
	if (!input)
	{
		printf("\n");
		return (FALSE);
	}
	if (!*input)
		return (TRUE);
	input = expand(lst_env, input);
	lst_tokens.node = 0;
	if (!is_closed(input))
		return (FALSE);
	lst_tokens = *lexical_analysis(input, &lst_tokens);
	if (!parsing(&lst_tokens, lst_env, input))
		return (TRUE);
	exec_list = *execution(&lst_tokens, &exec_list, lst_env);
	release_memory(&lst_tokens, &exec_list, input);
	return (TRUE);
}
