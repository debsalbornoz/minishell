/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:28:36 by jraupp            #+#    #+#             */
/*   Updated: 2024/05/30 20:23:57 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_list(t_list *list, void (f)(t_list *))
{
	if (!list)
		return ;
	if (list->node)
	{
		list->node = list->head;
		while (list->node->next)
		{
			list->head = list->node->next;
			f(list);
			list->node = list->head;
		}
		f(list);
	}
}

void	free_lst_tokens(t_list *tokens)
{
	free(tokens->node->data->token->value);
	free(tokens->node->data->token);
	free(tokens->node->data);
	free(tokens->node);
}

void	free_lst_env(t_list *envp)
{
	free(envp->node->data->env->name);
	free(envp->node->data->env->value);
	free(envp->node->data->env);
	free(envp->node->data);
	free(envp->node);
}

void	free_lst_exec(t_list *exec)
{
	free_matrix(exec->node->data->execution->command_table);
	free_matrix(exec->node->data->execution->redirects_and_files);
	free_matrix(exec->node->data->execution->envp);
	free(exec->node->data->execution->path);
	free(exec->node->data->execution->eofs);
	free(exec->node->data->execution);
	free(exec->node->data);
	free(exec->node);
}

void	release_memory(t_list *tokens, t_list *exec, char *input)
{
	free_list(exec, free_lst_exec);
	free_list(tokens, free_lst_tokens);
	free(input);
}
