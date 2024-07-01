/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:18:25 by codespace         #+#    #+#             */
/*   Updated: 2024/07/01 12:03:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_pipes(t_list *exec)
{
	t_node	*current_node;
	int		num_pipes;

	num_pipes = 0;
	current_node = exec->head;
	while (current_node != NULL && current_node->next != NULL)
	{
		num_pipes++;
		current_node = current_node->next;
	}
	return (num_pipes);
}

int	**create_pipes(int num_pipes)
{
	int	**pipes;
	int	i;

	pipes = ft_calloc(num_pipes, sizeof(int *));
	i = 0;
	if (!pipes)
	{
		perror("pipe:");
		return (NULL);
	}
	while (i < num_pipes)
	{
		pipes[i] = ft_calloc(2, sizeof(int));
		if (!pipes[i])
			return (NULL);
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe: ");
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	close_pipes(int command_index, int **pipes, int num_pipes)
{
	if (command_index > 0)
		close(pipes[command_index - 1][0]);
	if (command_index < num_pipes)
		close(pipes[command_index][1]);
}
