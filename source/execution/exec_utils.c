/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:59:18 by codespace         #+#    #+#             */
/*   Updated: 2024/06/01 18:24:39 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_file(int type)
{
	if (type == OUTPUT_FILE || type == INPUT_FILE
		|| type == APPEND_FILE || type == HEREDOC_KEY)
		return (1);
	return (0);
}

int	is_file_redirect_or_pipe(int type)
{
	if (find_file(type) || find_redirect(type) || type == PIPE)
		return (1);
	else
		return (0);
}

int	validate_command(t_node *exec)
{
	if (exec->data->exec->path != NULL
		&& exec->data->exec->command_table != NULL
		&& exec->data->exec->envp != NULL)
		return (1);
	return (0);
}

void	get_index(t_list *exec)
{
	t_node	*aux;
	int		i;

	aux = exec->head;
	i = 0;
	while (aux)
	{
		aux->data->exec->index = i;
		aux = aux->next;
	}
}

int	is_simple_command(t_list *tokens)
{
	t_node	*aux;

	aux = tokens->head;
	while (aux != NULL)
	{
		if (aux->data->token->type == PIPE)
			return (0);
		aux = aux->next;
	}
	aux = tokens->head;
	return (1);
}
