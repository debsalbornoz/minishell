/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:22:11 by dlamark-          #+#    #+#             */
/*   Updated: 2024/04/10 19:52:37 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_env_list(t_list *lst_env, char *name, char *value)
{
	if (lst_env)
		lst_env->node = lst_env->head;
	while (lst_env->node->next)
	{
		if (ft_strncmp(lst_env->node->data->env->name, name, 100) == 0)
		{
			lst_env->node->data->env->value = ft_strdup(value);
			return ;
		}
		lst_env->node = lst_env->node->next;
	}
	if (lst_env->node)
	{
		if (ft_strncmp(lst_env->node->data->env->name, name, 100) == 0)
		{
			free(lst_env->node->data->env->value);
			lst_env->node->data->env->value = ft_strdup(value);
			return ;
		}
		lst_env = add_node(lst_env);
		lst_env->node->data = ft_calloc(1, sizeof(union u_data));
		lst_env->node->data->env = ft_calloc(1, sizeof(t_env));
		lst_env->node->data->env->name = ft_strdup(name);
		lst_env->node->data->env->value = ft_strdup(value);
	}
}

char	*return_value_of_variable(char *name, t_list *lst_env)
{
	if (lst_env)
		lst_env->node = lst_env->head;
	while (lst_env->node)
	{
		if (ft_strncmp(lst_env->node->data->env->name, name, 1000) == 0)
			return (lst_env->node->data->env->value);
		lst_env->node = lst_env->node->next;
	}
	return (NULL);
}
