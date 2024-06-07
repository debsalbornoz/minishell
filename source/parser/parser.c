/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 20:07:44 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/07 14:29:12 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parser(t_list *tokens, t_list	*envp, char *input)
{
	tokens = type_assignment(tokens);
	if (syntax_error(tokens, envp, input))
		return (0);
	tokens = handle_heredoc(tokens);
	if (!tokens)
		return (0);
	tokens = remove_quotes(tokens);
	return (1);
}
