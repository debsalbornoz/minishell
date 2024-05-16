/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/16 16:30:19 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_command_table(t_list *tokens, t_list *exec)
{
	tokens->node = tokens->head;
	exec->node = exec->head;
	if (is_simple_command(tokens) && exec)
		create_simple_cmd_table(tokens, exec);
	else
		create_multi_cmd_table(tokens, exec, 0);
	tokens->node = tokens->head;
	exec->node = exec->head;
}

char	**allocate_cmd_table(t_node *tokens)
{
	int		counter;
	t_node	*aux;
	char	**command_table;

	aux = tokens;
	command_table = NULL;
	counter = 0;
	while (aux)
	{
		if (!find_redirect(aux->data->token->type)
			&& !find_file(aux->data->token->type))
			counter++;
		if (aux->data->token->type == PIPE)
			break ;
		aux = aux->next;
	}
	command_table = ft_calloc(counter + 1, sizeof(char *));
	if (!command_table)
		return (NULL);
	return (command_table);
}

void	create_simple_cmd_table(t_list	*tokens, t_list *exec)
{
	t_node	*aux_tokens;
	char	**command_table;
	int		i;

	aux_tokens = tokens->head;
	command_table = NULL;
	i = 0;
	command_table = allocate_cmd_table(aux_tokens);
	while (aux_tokens)
	{
		if (!find_redirect(aux_tokens->data->token->type)
			&& !find_file(aux_tokens->data->token->type))
		{
			command_table[i] = ft_strdup(aux_tokens->data->token->value);
			i++;
		}
		aux_tokens = aux_tokens->next;
	}
	command_table[i] = NULL;
	exec->node->data->execution->command_table = command_table;
}

void	create_multi_cmd_table(t_list *tokens, t_list *exec, int i)
{
	char	**command_table;

	command_table = NULL;
	while (exec->node)
	{
		command_table = allocate_cmd_table(tokens->node);
		while (tokens->node)
		{
			if (!is_file_redirect_or_pipe(tokens->node->data->token->type))
			{
				command_table[i] = ft_strdup(tokens->node->data->token->value);
				i++;
			}
			if (tokens->node->data->token->type == PIPE && tokens->node->next)
			{
				tokens->node = tokens->node->next;
				break ;
			}
			tokens->node = tokens->node->next;
		}
		command_table[i] = NULL;
		exec->node->data->execution->command_table = command_table;
		exec->node = exec->node->next;
		i = 0;
	}
}
