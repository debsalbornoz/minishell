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
	int		counter;
	t_node	*aux_exec;

	aux_exec = exec->head;
	aux_tokens = tokens->head;
	command_table = NULL;
	counter = count(aux_tokens);
	i = 0;
	command_table = ft_calloc(counter + 1, sizeof(char *));
	while (aux_tokens)
	{
		if (!find_redirect(aux_tokens->data->token->type) && !find_file(aux_tokens->data->token->type))
		{
			command_table[i] = ft_strdup(aux_tokens->data->token->value);
			aux_tokens = aux_tokens->next;
			i++;
		}
	}
	command_table[i] = NULL;
	exec->node->data->execution->command_table = command_table;
	aux_exec = exec->head;
	while (aux_exec)
	{
		print_command_table(aux_exec->data->execution->command_table);
		printf("\n");
		aux_exec = aux_exec->next;
	}
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
	while (aux_exec)
	{
		int counter = count(aux_tokens) + 1;
		command_table = ft_calloc (counter, sizeof(char *));
		while(aux_tokens)
		{
			if (!find_redirect(aux_tokens->data->token->type) && !find_file(aux_tokens->data->token->type) && aux_tokens->data->token->type != PIPE)
			{
				command_table[i] = ft_strdup(aux_tokens->data->token->value);
				i++;
			}
			if (aux_tokens->data->token->type == PIPE)
			{
				if (aux_tokens->next)
				{
					aux_tokens = aux_tokens->next;
					break;
				}
			}
			aux_tokens = aux_tokens->next;
		}
		command_table[i] = NULL;
		aux_exec->data->execution->command_table = command_table;
		aux_exec = aux_exec->next;
		i = 0;
	}
	aux_exec = exec->head;
	while (aux_exec)
	{
		print_command_table(aux_exec->data->execution->command_table);
		printf("\n");
		aux_exec = aux_exec->next;
	}
}

int	find_file(int type)
{
	if (type == OUTPUT_FILE || type == INPUT_FILE || type == APPEND_FILE ||type == HEREDOC_KEY)
		return (1);
	return (0);
}

void	print_command_table(char **command_table)
{
	int	i;

	i = 0;
	while (command_table[i] != NULL)
	{
		printf("%s - ", command_table[i]);
		i++;
	}
}

int count(t_node *node)
{
	int	i;

	i = 0;
	while (node)
	{
		if (!find_redirect(node->data->token->type) && !find_file(node->data->token->type))
			i++;
		if (node->data->token->type == PIPE)
			break;
		node = node->next;
	}
	return (i);
}
