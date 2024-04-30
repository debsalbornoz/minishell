/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:28:36 by jraupp            #+#    #+#             */
/*   Updated: 2024/04/29 17:51:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_list(t_list *list, void (f)(t_list *))
{
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

void	free_lst_tokens(t_list *lst_tokens)
{
	free(lst_tokens->node->data->token->value);
	free(lst_tokens->node->data->token);
	free(lst_tokens->node->data);
	free(lst_tokens->node);
}

void	free_lst_env(t_list *lst_env)
{
	free(lst_env->node->data->env->name);
	free(lst_env->node->data->env->value);
	free(lst_env->node->data->env);
	free(lst_env->node->data);
	free(lst_env->node);
}

void	free_lst_exec(t_list *lst_exec)
{
	lst_exec->node = lst_exec->head;
	free_matrix(lst_exec->node->data->execution->command_table);
	free_matrix(lst_exec->node->data->execution->envp);
	free(lst_exec->node->data->execution->path);
	free(lst_exec->node->data->execution);
	free(lst_exec->node->data);
	free(lst_exec->node);
}

void	release_memory(t_list *lst_tokens, t_list *exec_list, char *input)
{
	free_list(exec_list, free_lst_exec);
	free_list(lst_tokens, free_lst_tokens);
	free(input);
}
