/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 20:07:44 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/10 20:08:21 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parsing(t_list *lst_tokens, t_list	*lst_env, char *input)
{
	if (syntax_error(lst_tokens, lst_env, input))
		return (0);
	lst_tokens = remove_quotes(lst_tokens);
	return (1);
}
