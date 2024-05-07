/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 20:07:44 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/07 17:46:19 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parser(t_list *lst_tokens, t_list	*envp, char *input)
{
	lst_tokens = type_assignment(lst_tokens);
	if(!is_closed(input) ||syntax_error(lst_tokens, envp, input))
		return (0);
	lst_tokens = remove_quotes(lst_tokens);
	return (1);
}
