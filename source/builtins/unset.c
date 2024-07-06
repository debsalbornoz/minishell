/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:36:27 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/31 20:36:31 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static void	free_node_env(t_node *envp);

int	mini_unset(char **exec, t_list *envp)
{
	t_node	*unset_var;

	unset_var = envp->node;
	if (!ft_str_exist(*(exec + 1)))
		return (0);
	while (++exec, ft_str_exist(*exec))
	{
		if (exist_var(envp, *exec))
		{
			if (envp->node == envp->head)
			{
				envp->head = envp->node->next;
				free_node_env(envp->node);
			}
			else
			{
				unset_var = envp->node->next;
				envp->node->next = envp->node->next->next;
				free_node_env(unset_var);
			}
		}
	}
	return (0);
}

static void	free_node_env(t_node *envp)
{
	free(envp->data->env->name);
	free(envp->data->env->value);
	free(envp->data->env);
	free(envp->data);
	free(envp);
}
