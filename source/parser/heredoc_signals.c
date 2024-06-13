/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:15:08 by codespace         #+#    #+#             */
/*   Updated: 2024/06/12 21:34:46 by dlamark-         ###   ########.fr       */
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

int	check_signals(char *input, char *filename, int fd_in)
{
	t_list	*envp;
	char	*exit_status;

	envp = data_env_addr();
	envp->node = envp->head;
	exit_status = ft_get_env("?");
	if (!ft_strncmp(exit_status, "130", 3))
	{
		unlink(filename);
		dup2(fd_in, 0);
		printf("\n");
		return (-1);
	}
	else if (!input)
	{
		printf("warning:here-document delimited by end-of-file(wanted `eof')\n");
		update_env_list(envp, "?", "131");
		return (1);
	}
	else
		return (0);
}
