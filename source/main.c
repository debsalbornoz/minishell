/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:51:39 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/23 18:18:22 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signal;

int	main(int argc, char **argv, char **envp)
{
	t_list	lst_env;

	(void)argv;
	if (argc > 1)
		return (0);
	lst_env.node = 0;
	lst_env = *make_lst_env(envp, &lst_env);
	while (program(&lst_env))
		;
	free_list(&lst_env, free_lst_env);
	return (EXIT_SUCCESS);
}
