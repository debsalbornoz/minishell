/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:18:25 by codespace         #+#    #+#             */
/*   Updated: 2024/06/15 17:05:43 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_pipes(t_list *tokens)
{
	t_node	*aux;
	int		counter;

	if (!tokens)
		return (-1);
	counter = 0;
	aux = tokens->head;
	while (aux)
	{
		if (aux->data->token->type == PIPE)
			counter++;
		aux = aux->next;
	}
	return (counter);
}

int	**create_pipes(t_list *tokens)
{
	int	counter;
	int	**pipes;

	counter = count_pipes(tokens);
	pipes = ft_calloc((counter + 1), sizeof(int *));
	return (pipes);
}
