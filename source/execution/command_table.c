/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/07 19:16:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_command_table(t_list *tokens, t_list *exec)
{
	if (is_simple_command(tokens) && exec)
	{
		create_simple_cmd_table(tokens, exec);
		return;
	}
	else
		create_multi_cmd_table(tokens, exec);
}

void	create_simple_cmd_table(t_list	*tokens, t_list *exec)
{
	t_node	*aux_tokens;
	char	**command_table;
	int		i;

	aux_tokens = tokens->head;
	command_table = NULL;
	i = 0;
	while (!find_redirect(aux_tokens->data->token->type) && !is_file(aux_tokens))
	{
		command_table[i] = ft_strdup(aux_tokens->data->token->value);
		aux_tokens = aux_tokens->next;
		i++;
	}
	exec->node->data->execution->command_table = command_table;
}
void	create_multi_cmd_table(t_list *tokens, t_list *exec)
{
	t_node	*aux_tokens;
	t_node	*aux_exec;
	char	**command_table;
	int		i;

	aux_tokens = tokens->head;
	aux_exec = exec->head;
	command_table = NULL;
	i = 0;
	while (aux_tokens && aux_exec)
	{
		if (!find_redirect(aux_tokens->data->token->type) && !find_file(aux_tokens) && aux_tokens->data->token->type != PIPE)
		{
			command_table[i] = ft_strdup(aux_tokens->data->token->value);
			i++;
		}
		if (aux_tokens->data->token->type == PIPE && aux_exec)
		{
			aux_exec->data->execution->command_table = command_table;
			if (aux_exec->next)
				aux_exec = aux_exec->next;
			i = 0;
		}
		aux_tokens = aux_tokens->next;
	}
	aux_exec = exec->head;
	while ()
}

int	find_file(int type)
{
	if (type == OUTPUT_FILE || type == INPUT_FILE || type == APPEND_FILE ||type == HEREDOC_KEY)
		return (1);
	return (0);
}
