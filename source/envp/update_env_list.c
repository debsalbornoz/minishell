/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:22:11 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/09 14:57:22 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env_list.h"

t_list	*update_env_list(t_list *lst_env, char *name, char *value)
{
	int	result;

	if (lst_env)
	{
		lst_env->node = lst_env->head;
		result = update_existing_node(lst_env, name, value);
		if (result == 0)
			return (lst_env);
		lst_env = add_new_node(lst_env, name, value);
	}
	return (lst_env);
}

int	update_existing_node(t_list *lst_env, char *name, char *value)
{
	while (lst_env->node->next)
	{
		if (ft_strncmp(lst_env->node->data->env->name, name, 1000) == 0)
		{
			if (ft_str_exist(lst_env->node->data->env->value))
				free(lst_env->node->data->env->value);
			if (value)
				lst_env->node->data->env->value = ft_strdup(value);
			else
				lst_env->node->data->env->value = 0;
			return (0);
		}
		lst_env->node = lst_env->node->next;
	}
	if (ft_strncmp(lst_env->node->data->env->name, name, 1000) == 0)
	{
		if (ft_str_exist(lst_env->node->data->env->value))
			free(lst_env->node->data->env->value);
		if (ft_str_exist(value))
			lst_env->node->data->env->value = ft_strdup(value);
		else
			lst_env->node->data->env->value = NULL;
		return (0);
	}
	return (-1);
}

t_list	*add_new_node(t_list *lst_env, char *name, char *value)
{
	lst_env = add_node(lst_env);
	lst_env->node->data = ft_calloc(1, sizeof(union u_data));
	lst_env->node->data->env = ft_calloc(1, sizeof(t_env));
	lst_env->node->data->env->name = ft_strdup(name);
	if (value)
		lst_env->node->data->env->value = ft_strdup(value);
	else
		lst_env->node->data->env->value = 0;
	return (lst_env);
}

char	*ft_get_env(char *name)
{
	t_list	*env;
	t_node	*aux;

	env = data_env_addr();
	env->node = env->head;
	aux = env->head;
	while (aux)
	{
		if (ft_strncmp(aux->data->env->name, name, ft_strlen(name)) == 0)
			return (aux->data->env->value);
		aux = aux->next;
	}
	return (NULL);
}

int	exist_var(t_list *envp, char *name)
{
	envp->node = envp->head;
	while (envp->node)
	{
		if (envp->node == envp->head
			&& !ft_strcmp(envp->node->data->env->name, name))
			return (1);
		if (envp->node->next
			&& !ft_strcmp(envp->node->next->data->env->name, name))
			return (1);
		if (envp->node->next)
			envp->node = envp->node->next;
		else
			break ;
	}
	return (envp->node = envp->head, 0);
}
