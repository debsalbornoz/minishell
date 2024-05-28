/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_and_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jackson <jackson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:11:54 by codespace         #+#    #+#             */
/*   Updated: 2024/05/28 10:21:05 by jackson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	get_redirects_and_files(t_list *exec, t_list *tokens)
{
	t_node	*aux_exec;
	char	**redir_and_files;

	aux_exec = exec->head;
	while (aux_exec)
	{
		redir_and_files = allocate_matrix(tokens);
		redir_and_files = fill_redir_and_files(&tokens->node, redir_and_files);
		aux_exec = aux_exec->next;
	}
}

int	get_size(t_node *tokens)
{
	int	counter;

	counter = 0;
	while (tokens)
	{
		if (find_redirect(tokens->data->token->type)
			|| find_file(tokens->data->token->type))
			counter++ ;
		if (tokens->data->token->type == PIPE)
			break ;
		tokens = tokens->next;
	}
	return (counter);
}

char	**allocate_matrix(t_list *tokens)
{
	int		counter;
	char	**redir_and_files;

	redir_and_files = NULL;
	counter = 0;
	while (tokens->node)
	{
		if (find_redirect(tokens->node->data->token->type)
			|| find_file(tokens->node->data->token->type))
			counter++;
		if (tokens->node->data->token->type == PIPE)
			break ;
		tokens->node = tokens->node->next;
	}
	redir_and_files = ft_calloc(counter + 1, sizeof(char *));
	if (!redir_and_files)
		return (NULL);
	return (redir_and_files);
}

char	**fill_redir_and_files(t_node **tokens, char **redir_and_files)
{
	int		i;
	t_node	*current;

	i = 0;
	current = *tokens;
	while (current)
	{
		if (find_redirect(current->data->token->type)
			|| find_redirect(current->data->token->type))
		{
			redir_and_files[i] = ft_strdup(current->data->token->value);
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
	redir_and_files[i] = NULL;
	return (redir_and_files);
}
