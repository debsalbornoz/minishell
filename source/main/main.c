/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:51:39 by jraupp            #+#    #+#             */
/*   Updated: 2024/07/09 19:33:36 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		res;
	t_list	*env_lst;

	(void)argc;
	(void)argv;
	res = 0;
	env_lst = data_env_addr();
	env_lst = create_env_list(envp, env_lst);
	env_lst = update_env_list(env_lst, "?", "0");
	handle_signal();
	while (program(env_lst))
		;
	res = get_env_error(env_lst);
	free_list(env_lst, free_lst_env);
	return (res);
}
