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

void	mini_env(t_list *envp)
{
	runs_on_list(envp, print_for_env);
}

static t_node	*print_for_env(t_node *no)
{
	return (printf("%s=%s\n", no->data->env->name, no->data->env->value), no);
}
