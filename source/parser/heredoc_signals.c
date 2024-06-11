/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:15:08 by codespace         #+#    #+#             */
/*   Updated: 2024/06/11 18:15:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_heredoc_signals(void)
{
	signal(SIGINT, handle_ctrlc_heredoc);
}

void	handle_ctrlc_heredoc(int signal)
{
	t_list	*envp;

	(void)signal;
	envp = data_env_addr();
	close(STDIN_FILENO);
	update_env_list(envp, "?", "130");
}
