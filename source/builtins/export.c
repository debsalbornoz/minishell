/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:35:44 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/31 20:37:54 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static t_node	*print_for_export(t_node *nde);

void	mini_export(t_list *envp)
{
	runs_on_list(envp, print_for_export);
}

static t_node	*print_for_export(t_node *nde)
{
	printf("declare -x %s=%s\n", nde->data->env->name, nde->data->env->value);
	return (nde);
}
