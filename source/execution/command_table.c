/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/17 19:02:48 by codespace        ###   ########.fr       */
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
		create_multi_cmd_table(tokens, exec);
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
		if (!is_file_redirect_or_pipe(aux->data->token->type))
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

void	create_multi_cmd_table(t_list *tokens, t_list *exec)
{
	char	**command_table;

	command_table = NULL;
	while (exec->node)
	{
		command_table = allocate_cmd_table(tokens->node);
		command_table = fill_command_table(&tokens->node, command_table);
		if (*command_table == NULL)
			free(command_table);
		else
		{
			exec->node->data->execution->command_table = command_table;
			exec->node = exec->node->next;
		}
	}
}

char	**fill_command_table(t_node **tokens, char **command_table)
{
	int		i;
	t_node	*current;

	i = 0;
	current = *tokens;
	while (current)
	{
		if (!is_file_redirect_or_pipe(current->data->token->type))
		{
			command_table[i] = ft_strdup(current->data->token->value);
			i++;
		}
		else if (current->data->token->type == PIPE && current->next)
		{
			current = current->next;
			break ;
		}
		current = current->next;
	}
	*tokens = current;
	command_table[i] = NULL;
	return (command_table);
}
