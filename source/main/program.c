/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:46:23 by jraupp            #+#    #+#             */
/*   Updated: 2024/04/10 20:00:48 by dlamark-         ###   ########.fr       */
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
		printf("\n");
		return (FALSE);
	}
	input = expand(lst_env, input);
	if (!*input)
		return (TRUE);
	input = expand(lst_env, input);
	if (!*input)
		return (TRUE);
	lst_tokens.node = 0;
	if (!is_closed(input))
	{
		printf("Fatal error: unclosed quotes\n");
		return (FALSE);
	}
	lst_tokens = *lexical_analysis(input, &lst_tokens);
	if (!parsing(&lst_tokens, lst_env, input))
		return (TRUE);
	exec_list = *create_execution_list(&lst_tokens, &exec_list, lst_env);
	lst_tokens.node = lst_tokens.head;
	free_list(&lst_tokens, free_lst_tokens);
	free_list(&exec_list, free_lst_exec);
	free(input);
	return (TRUE);
}
