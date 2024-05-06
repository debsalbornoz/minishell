/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_assignment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:26:00 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/24 14:10:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_list	*type_assignment(t_list *lst_tokens)
{
	lst_tokens->head = is_command_part1(lst_tokens->head);
	lst_tokens = runs_on_list(lst_tokens, is_command_part2);
	lst_tokens = runs_on_list(lst_tokens, is_path);
	lst_tokens = runs_on_list(lst_tokens, is_argument);
	lst_tokens = runs_on_list(lst_tokens, is_builtin);
	lst_tokens = runs_on_list(lst_tokens, is_file);
	lst_tokens = runs_on_list(lst_tokens, is_heredoc_key);
	return (lst_tokens);
}
