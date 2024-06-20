/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:34:42 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/19 22:46:56 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	mini_echo(t_list *token)
{
	int	newline;

	newline = 0;
	token->node = token->node->next;
	while (token->node && (token->node->data->token->type != PIPE))
	{
		if (!ft_strcmp(token->node->data->token->value, "-n"))
			newline++;
		printf("%s", token->node->data->token->value);
		if (token->node->next)
		{
			printf(" ");
			token->node = token->node->next;
		}
		else
			break ;
	}
	if (!newline)
		printf("\n");
}
