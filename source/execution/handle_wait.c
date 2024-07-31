/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:24:21 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/28 19:40:27 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	wait_for_children(t_list *envp, int *pids, int num_process, int i)
{
	char	*sts;
	int		status;
	char	*last_command;

	sts = NULL;
	last_command = NULL;
	while (waitpid(pids[i], &status, 0) != -1)
	{
		if (WIFEXITED(status))
		{
			if (i == num_process - 1)
				last_command = ft_itoa(WEXITSTATUS(status));
			sts = update_sts(sts, status);
		}
		else if (WIFSIGNALED(status))
		{
			sts = update_signal_sts(status, sts);
			if (ft_strcmp(sts, "130") == 0 ||ft_strcmp(sts, "131") == 0)
				last_command = ft_strdup(sts);
		}
		else
			free_strs(sts, last_command, 0);
		i++;
	}
	update_env_list(envp, "?", last_command);
	free_strs(sts, last_command, 1);
}

void	free_strs(char *status, char *last_command, int flag)
{
	if (flag == 0)
	{
		if (status)
			free(status);
		status = NULL;
	}
	else if (flag == 1)
	{
		if (status)
			free(status);
		if (last_command)
			free(last_command);
	}
}

char	*update_sts(char *sts, int status)
{
	if (sts)
		free(sts);
	sts = ft_itoa(WEXITSTATUS(status));
	return (sts);
}

char	*update_signal_sts(int status, char *sts)
{
	int	signal;

	signal = WTERMSIG(status);
	if (signal == 130 || signal == 131)
	{
		if (sts)
		free(sts);
		if (signal == SIGINT)
			sts = ft_strdup("130");
		else if (signal == SIGQUIT)
		{
			sts = ft_strdup("131");
			ft_printf("Quit (core dumped)\n");
		}
	}
	return (sts);
}
