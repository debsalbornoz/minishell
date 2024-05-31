/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:28:36 by jraupp            #+#    #+#             */
/*   Updated: 2024/05/31 15:33:28 by jraupp           ###   ########.fr       */
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
	free_matrix(exec->node->data->exec->command_table);
	free_matrix(exec->node->data->exec->redirs_files);
	free_matrix(exec->node->data->exec->envp);
	free_matrix(exec->node->data->exec->eofs);
	free(exec->node->data->exec->path);
	free(exec->node->data->exec);
	free(exec->node->data);
	free(exec->node);
}

void	release_memory(t_list *tokens, t_list *exec, char *input)
{
	free_list(exec, free_lst_exec);
	free_list(tokens, free_lst_tokens);
	free(input);
}
