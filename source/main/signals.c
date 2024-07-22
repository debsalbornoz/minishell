/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:36:13 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/15 19:35:30 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sigint(int signal)
{
	t_list	*lst_env;

	(void)signal;
	lst_env = data_env_addr();
	set_error(lst_env);
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	if (readline_status(-1))
		rl_redisplay();
}

void	set_error(t_list *lst_env)
{
	if (lst_env)
		update_env_list(lst_env, "?", "130");
}

void	disable_signal(int signum)
{
	signal(signum, SIG_IGN);
}
