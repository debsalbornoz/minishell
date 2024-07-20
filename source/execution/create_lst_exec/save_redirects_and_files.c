/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_redirects_and_files.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:11:54 by codespace         #+#    #+#             */
/*   Updated: 2024/07/20 16:07:56 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	create_simple_redir_table(t_list	*tokens, t_list *exec);
void	allocate_multi_redir_table(t_list *tokens, t_list *exec);
void	create_multi_redir_table(t_list *tokens, t_list *exec);
char	**allocate_redir_table(t_node *tokens);
void	fill_redir_and_files(t_list *tokens, t_list *exec);

void	create_redir_table(t_list *tokens, t_list *exec)
{
	if (is_simple_command(tokens) && exec)
		create_simple_redir_table(tokens, exec);
	else
		create_multi_redir_table(tokens, exec);
	tokens->node = tokens->head;
	exec->node = exec->head;
}

void	create_simple_redir_table(t_list	*tokens, t_list *exec)
{
	t_node	*aux_tokens;
	char	**redir_and_files;
	int		i;

	aux_tokens = tokens->head;
	redir_and_files = NULL;
	i = 0;
	redir_and_files = allocate_redir_table(aux_tokens);
	if (!redir_and_files)
		return ;
	while (aux_tokens)
	{
		if (find_redirect(aux_tokens->data->token->type)
			|| find_file(aux_tokens->data->token->type))
		{
			redir_and_files[i] = ft_strdup(aux_tokens->data->token->value);
			i++;
		}
		aux_tokens = aux_tokens->next;
	}
	redir_and_files[i] = NULL;
	exec->node->data->exec->redir_and_files = redir_and_files;
}

void	allocate_multi_redir_table(t_list *tokens, t_list *exec)
{
	t_node	*aux_exec;
	t_node	*aux_tokens;
	int		counter;

	aux_exec = exec->head;
	aux_tokens = tokens->head;
	counter = 0;
	while (aux_tokens)
	{
		if (is_file_redirect_or_pipe(aux_tokens->data->token->type))
		{
			if (aux_tokens->data->token->type != PIPE)
				counter++;
		}
		if (aux_tokens->data->token->type == PIPE && aux_exec->next)
		{
			if (counter > 0)
			{
				aux_exec->data->exec->redir_and_files = ft_calloc(counter + 1, sizeof(char *));
			}
				aux_exec = aux_exec->next;
				counter = 0;
		}
		aux_tokens = aux_tokens->next;
	}
	if (aux_exec->next == NULL)
	{
		if (counter > 0)
			aux_exec->data->exec->redir_and_files = ft_calloc(counter + 1, sizeof(char *));
	}
}

void	create_multi_redir_table(t_list *tokens, t_list *exec)
{
	allocate_multi_redir_table(tokens, exec);
	fill_redir_and_files(tokens, exec);
}

void	fill_redir_and_files(t_list *tokens, t_list *exec)
{
	int		i;
	t_node	*aux_token;
	t_node	*aux_exec;

	i = 0;
	aux_token = tokens->head;
	aux_exec = exec->head;
	while (aux_token)
	{
		if (is_file_redirect_or_pipe(aux_token->data->token->type))
		{
			if (aux_token->data->token->type != PIPE)
			{
				aux_exec->data->exec->redir_and_files[i] = ft_strdup(aux_token->data->token->value);
				i++;
			}
		}
		if (aux_token->data->token->type == PIPE && aux_exec->next)
		{
			aux_exec = aux_exec->next;
			i = 0;
		}
		aux_token = aux_token->next;
	}
}

char	**allocate_redir_table(t_node *tokens)
{
	int		counter;
	t_node	*aux;
	char	**redir_and_files;

	aux = tokens;
	redir_and_files = NULL;
	counter = 0;
	while (aux)
	{
		if (is_file_redirect_or_pipe(aux->data->token->type))
		{
			if (aux->data->token->type != PIPE)
				counter++;
		}
			counter++;
		if (aux->data->token->type == PIPE)
			break ;
		aux = aux->next;
	}
	if (counter > 0)
		redir_and_files = ft_calloc(counter + 1, sizeof(char *));
	if (!redir_and_files)
		return (NULL);
	return (redir_and_files);
}


/*
void	save_redirects_and_files(t_list *exec, t_list *tokens)
{
	char	**redir_and_files;

	redir_and_files = NULL;
	while (exec->node)
	{
		redir_and_files = allocate_redir_and_files(tokens->node);
		if (redir_and_files)
		{
			redir_and_files = get_redirects_and_files(&tokens->node,
					redir_and_files);
			exec->node->data->exec->redir_and_files = redir_and_files;
			exec->node = exec->node->next;
		}
		if (!redir_and_files)
		{
			while (tokens->node->data->token->type != PIPE
				&& tokens->node->next)
				tokens->node = tokens->node->next;
			if (tokens->node->data->token->type == PIPE && tokens->node->next)
				tokens->node = tokens->node->next;
			exec->node = exec->node->next;
		}
	}
	tokens->node = tokens->head;
	exec->node = exec->head;
}

char	**allocate_redir_and_files(t_node *tokens)
{
	int		counter;
	t_node	*aux;
	char	**redir_and_files;

	aux = tokens;
	redir_and_files = NULL;
	counter = 0;
	while (aux)
	{
		if (find_redirect(aux->data->token->type)
			|| find_file(aux->data->token->type))
			counter++;
		if (aux->data->token->type == PIPE)
			break ;
		aux = aux->next;
	}
	if (counter > 0)
		redir_and_files = ft_calloc(counter + 1, sizeof(char *));
	if (!redir_and_files)
		return (NULL);
	return (redir_and_files);
}

char	**get_redirects_and_files(t_node **tokens, char **redir_and_files)
{
	int		i;
	t_node	*current;

	i = 0;
	current = *tokens;
	while (current)
	{
		if (find_redirect(current->data->token->type)
			|| find_file(current->data->token->type))
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
*/
