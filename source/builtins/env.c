/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:07:48 by jraupp            #+#    #+#             */
/*   Updated: 2024/05/30 17:06:13 by jraupp           ###   ########.fr       */
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
