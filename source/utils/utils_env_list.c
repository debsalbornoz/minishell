/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:22:11 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/23 15:29:34 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_env_list(t_list *lst_env, char *name, char *value)
{
	if (lst_env)
		lst_env->node = lst_env->head;
	while (lst_env->node)
	{
		if (ft_strncmp(lst_env->node->data->env->name, name, 100) == 0)
		{
			lst_env->node->data->env->value = ft_strdup(value);
			return;
		}
		lst_env->node = lst_env->node->next;
	}
	if(lst_env->node == NULL)
	{
		add_node(lst_env);
		lst_env->node->data->env->name = NULL;
		lst_env->node->data->env->value = NULL;

	}
}


t_list **data_env_addr(void)
{
	static t_list	*lst_env = NULL;

	return (&lst_env);
}

void init_data_env_addr(char **envp)
{
    t_list **addr;

    addr = data_env_addr();
    *addr = make_lst_env(envp);
}