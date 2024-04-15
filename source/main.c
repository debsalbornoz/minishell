/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:51:39 by jraupp            #+#    #+#             */
/*   Updated: 2024/04/10 20:38:26 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*lst_env;
	lst_env = NULL;
	(void)argv;
	if (argc > 1)
		return (0);
	init_data_env_addr(envp);
	lst_env = *data_env_addr();
	handle_signal(lst_env);
	while (program(lst_env))
		;
	lst_env->node = lst_env->head;
	free_list(lst_env, free_lst_env);
	free(lst_env);
	return (EXIT_SUCCESS);
}
