/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_redirects_and_files.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:11:54 by codespace         #+#    #+#             */
/*   Updated: 2024/05/25 16:41:52 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**allocate_redir_and_files(t_node *tokens)
{
	int			counter;
	t_node		*aux;
	char		**redir_and_files;

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
