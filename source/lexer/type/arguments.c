/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:25:59 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/20 20:57:14 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_node	*is_argument(t_node *node)
{
	if (node->data->token->type == WORD && node->data->token->type != COMMAND)
		node->data->token->type = ARGUMENT;
	return (node);
}
