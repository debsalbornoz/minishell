/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_assignment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:26:00 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/20 15:40:40 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*type_assignment(t_list *lst_tokens)
{
	lst_tokens->head = is_command_part1(lst_tokens->head);
	lst_tokens = runs_on_list(lst_tokens, is_command_part2);
	lst_tokens = runs_on_list(lst_tokens, is_argument);
	lst_tokens = runs_on_list(lst_tokens, is_builtin);
	lst_tokens = runs_on_list(lst_tokens, is_file);
	lst_tokens = runs_on_list(lst_tokens, is_append_or_heredoc_key);
	return (lst_tokens);
}
