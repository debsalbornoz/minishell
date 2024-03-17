/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_assignment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:26:00 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/17 13:41:25 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*type_assignment(t_list *tokens)
{
	tokens = is_command(tokens);
	tokens = is_builtin(tokens);
	tokens = is_file(tokens);
	tokens = is_heredoc_key(tokens);
	return (tokens);
}
