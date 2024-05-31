/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:05:22 by jraupp            #+#    #+#             */
/*   Updated: 2024/05/30 17:19:15 by jraupp           ###   ########.fr       */
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
