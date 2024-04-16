/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:51:39 by jraupp            #+#    #+#             */
/*   Updated: 2024/04/07 21:14:29 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*lst_env;

	(void)argv;
	if (argc > 1)
		return (0);
	lst_env = data_env_addr();
	lst_env = make_lst_env(envp, lst_env);
	handle_signal();
	while (program(lst_env))
		;
	free_list(lst_env, free_lst_env);
	return (EXIT_SUCCESS);
}
