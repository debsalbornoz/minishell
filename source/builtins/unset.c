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

int	mini_unset(char **exec, t_list *envp)
{
	if (!ft_str_exist(*(exec + 1)))
		return (0);
	while (++exec, ft_str_exist(*exec))
	{
		if (exist_var(envp, *exec))
		{
			while (envp->node->next)
			{
				envp->node->data->env = envp->node->next->data->env;
				envp->node = envp->node->next;
			}
			free_lst_env(envp);
		}
	}
	return (0);
}
