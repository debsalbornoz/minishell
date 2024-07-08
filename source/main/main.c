/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:51:39 by jraupp            #+#    #+#             */
/*   Updated: 2024/07/07 17:12:36 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_env_error(t_list *envp);

int	main(int argc, char **argv, char **envp)
{
	int		res;
	t_list	*env_lst;

	(void)argc;
	(void)argv;
	res = 0;
	env_lst = data_env_addr();
	env_lst = create_env_list(envp, env_lst);
	handle_signal();
	update_env_list(env_lst , "?", 0);
	while (program(env_lst))
		;
	res = get_env_error(env_lst);
	free_list(env_lst, free_lst_env);
	return (res);
}

static int	get_env_error(t_list *envp)
{
	envp->node = envp->head;
	while (envp->node)
	{
		if (!ft_strcmp(envp->node->data->env->name, "?"))
			return (ft_atoi(envp->node->data->env->value));
		if (envp->node->next)
			envp->node = envp->node->next;
		else
			break ;
	}
	return (0);
}
