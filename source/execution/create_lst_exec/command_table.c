/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/01 12:17:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	create_command_table(t_list *tokens, t_list *exec)
{
	if (is_simple_command(tokens) && exec)
		create_simple_cmd_table(tokens, exec);
	else
		create_multi_cmd_table(tokens, exec);
	tokens->node = tokens->head;
	exec->node = exec->head;
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
	if (!command_table)
		return ;
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
	exec->node->data->exec->command_table = command_table;
}

void allocate_multi_cmd_table(t_list *tokens, t_list *exec)
{
	t_node	*aux_exec;
	t_node	*aux_tokens;
	int		counter;

	aux_exec = exec->head;
	aux_tokens = tokens->head;
	counter = 0;
	while (aux_tokens)
	{
		if (!is_file_redirect_or_pipe(aux_tokens->data->token->type))
			counter++;
		if (aux_tokens->data->token->type == PIPE && aux_exec->next)
		{
			if (counter > 0)
			{
				aux_exec->data->exec->command_table = ft_calloc(counter + 1, sizeof(char *));
			}
				aux_exec = aux_exec->next;
				counter = 0;
		}
		aux_tokens = aux_tokens->next;
	}
	if (aux_exec->next == NULL)
	{
		if (counter > 0)
			aux_exec->data->exec->command_table = ft_calloc(counter + 1, sizeof(char *));
	}
}
void create_multi_cmd_table(t_list *tokens, t_list *exec)
{
	allocate_multi_cmd_table(tokens, exec);
	fill_command_table(tokens, exec);
}

void fill_command_table(t_list *tokens, t_list *exec)
{
	int		i;
	t_node	*aux_token;
	t_node	*aux_exec;

	i = 0;
	aux_token = tokens->head;
	aux_exec = exec->head;
	while (aux_token)
	{
		if (!is_file_redirect_or_pipe(aux_token->data->token->type))
		{
			aux_exec->data->exec->command_table[i] = ft_strdup(aux_token->data->token->value);
			i++;
		}
		else if (aux_token->data->token->type == PIPE && aux_exec->next)
		{
			aux_exec = aux_exec->next;
			i = 0;
		}
		aux_token = aux_token->next;
	}
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
	if (counter > 0)
		command_table = ft_calloc(counter + 1, sizeof(char *));
	if (!command_table)
		return (NULL);
	return (command_table);
}
