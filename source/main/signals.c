/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:36:13 by dlamark-          #+#    #+#             */
/*   Updated: 2024/03/23 18:14:49 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_sigint(int signal)
{
	extern int	g_signal;

	(void)signal;
	rl_replace_line("", 0);
	rl_on_new_line();
	printf("\n");
	rl_redisplay();
	g_signal = 1;
}

void	handle_signal(t_list *lst_env)
{
	extern int	g_signal;

	(void)lst_env;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	set_error(lst_env);
}

void	set_error(t_list *lst_env)
{
	extern int	g_signal;

	if (lst_env && g_signal == 1)
	{
		printf("???");
		update_env_list(lst_env, "$", "130");
		runs_on_list(lst_env, print_lst_env);
		g_signal = 0;
	}
}

// void	handle_signal(t_list	*lst_env)
// {
// 	struct sigaction	sa;

// 	sa.sa_sigaction = handle_sigint;
// 	sa.sa_data = (void *)lst_env;
// 	sigemptyset(&sa.sa_mask);
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGQUIT, &sa, NULL);

// }
