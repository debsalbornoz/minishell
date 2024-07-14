/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:46:23 by jraupp            #+#    #+#             */
/*   Updated: 2024/07/09 19:34:01 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	readline_status(int sts);

int	program(t_list *envp)
{
	char		*input;
	t_list		tokens;
	t_list		exec;

	tokens.node = 0;
	exec.node = 0;
	readline_status(1);
	input = readline("¯\\_(ツ)_/¯: ");
	readline_status(0);
	if (!input)
	{
		printf("exit\n");
		return (FALSE);
	}
	if (!*input)
		return (TRUE);
	input = trim_start_spaces(input);
	if (!input)
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

int	readline_status(int sts)
{
	static int	status;

	if (sts != -1)
		status = sts;
	return (status);
}
