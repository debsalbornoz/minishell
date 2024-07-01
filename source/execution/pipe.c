/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:18:25 by codespace         #+#    #+#             */
/*   Updated: 2024/07/01 14:16:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	setup_pipes(int command_index, int fd_in, int fd_out, int **pipes)
{
	int		i;
	int		num_pipes;

	i = 0;
	num_pipes = count_pipes2(pipes);
	if (command_index > 0)
		dup2(pipes[command_index - 1][0], 0);
	else
		dup2(fd_in, 0);
	if (command_index < num_pipes)
		dup2(pipes[command_index][1], 1);
	else
		dup2(fd_out, 1);
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	count_pipes2(int **pipes)
{
	int	i;

	i = 0;
	while (pipes[i] != NULL)
		i++;
	return (i);
}

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

	pipes = ft_calloc(num_pipes + 1, sizeof(int *));
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
	pipes[i] = NULL;
	return (pipes);
}

void	close_pipes(int command_index, int **pipes, int num_pipes)
{
	if (command_index > 0)
		close(pipes[command_index - 1][0]);
	if (command_index < num_pipes)
		close(pipes[command_index][1]);
}
