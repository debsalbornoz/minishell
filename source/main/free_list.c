/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:28:36 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/20 14:03:07 by jraupp           ###   ########.fr       */
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
	if (*lst_env->node->data->env->value)
		free(lst_env->node->data->env->value);
	free(lst_env->node->data->env);
	free(lst_env->node->data);
	free(lst_env->node);
}
