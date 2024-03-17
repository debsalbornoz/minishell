/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_assignment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:26:00 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/17 15:33:37 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*type_assignment(t_list *tokens)
{
	tokens = is_command(tokens);
	tokens = is_argument(tokens);
	tokens = is_builtin(tokens);
	tokens = is_file(tokens);
	tokens = is_append_or_heredoc_key(tokens);
	return (tokens);
}
