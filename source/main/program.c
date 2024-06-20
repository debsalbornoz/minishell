/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:46:23 by jraupp            #+#    #+#             */
/*   Updated: 2024/06/20 18:35:32 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	program(t_list *envp)
{
	char		*input;
	t_list		tokens;
	t_list		exec;

	tokens.node = 0;
	exec.node = 0;
	input = readline("¯\\_(ツ)_/¯: ");
	if (!input)
	{
		printf("exit\n");
		update_env_list(envp, "?", "131");
		return (FALSE);
	}
	if (!*input)
		return (TRUE);
	input = expand(envp, input);
	if (!is_closed(input, envp))
		return (TRUE);
	tokens = *lexer(&tokens, input);
	if (!parser(&tokens, envp, input))
		return (TRUE);
	tokens.node = tokens.head;
	if (execute(&tokens, &exec, envp, input))
		return (FALSE);
	return (TRUE);
}
