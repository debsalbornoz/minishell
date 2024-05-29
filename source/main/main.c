/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jackson <jackson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:51:39 by jraupp            #+#    #+#             */
/*   Updated: 2024/05/29 13:31:43 by jackson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*env_lst;

	(void)argc;
	(void)argv;
	env_lst = data_env_addr();
	env_lst = create_env_list(envp, env_lst);
	handle_signal();
	while (program(env_lst))
		;
	free_list(env_lst, free_lst_env);
	return (EXIT_SUCCESS);
}
