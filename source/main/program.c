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

	lst_tokens.node = 0;
	input = readline("¯\\_(ツ)_/¯: ");
	if (check_input(input) == 0)
		return (FALSE);
	if (check_input(input) == 1)
		return (TRUE);
	lst_tokens = *lexical_analysis(input, &lst_tokens);
	if (!parsing(&lst_tokens, lst_env, input))
		return (TRUE);
	free_list(&lst_tokens, free_lst_tokens);
	free(input);
	return (FALSE);
}
