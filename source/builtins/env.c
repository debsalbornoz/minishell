/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:34:59 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/31 20:41:43 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static t_node	*print_for_env(t_node *no);

int	mini_env(t_list *envp)
{
	return (runs_on_list(envp, print_for_env), 0);
}

static t_node	*print_for_env(t_node *node)
{
	if (is_not_ocult_var(node->data->env->name))
		printf("%s=%s\n", node->data->env->name, node->data->env->value);
	return (node);
}

int	is_not_ocult_var(char *name)
{
	return (ft_strcmp(name, "?") && ft_strcmp(name, "_"));
}
