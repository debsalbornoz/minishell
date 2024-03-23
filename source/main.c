/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:51:39 by jraupp            #+#    #+#             */
/*   Updated: 2024/03/23 18:32:20 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	sigint_handler(int sig, siginfo_t *info, void *context);

int	main(int argc, char **argv, char **envp)
{
	t_list	lst_env;
	// struct	sigaction	sa;

	// sa.sa_sigaction = sigint_handler;
	(void)argc;
	(void)argv;
	lst_env.node = 0;
	lst_env = *make_lst_env(envp, &lst_env);
	while (program(&lst_env))
		;
	free_list(&lst_env, free_lst_env);
	return (EXIT_SUCCESS);
}

// void	sigint_handler(int sig, siginfo_t *info, void *context)
// {
// 	(void)sig;
// }
