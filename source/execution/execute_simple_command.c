/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/09 18:24:34 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_simple_command(t_list *exec,
	t_list *tokens, t_list *envp, char *input)
{
	int		pid;
	int		ft_stdout;
	int		ft_stdin;
	int		status;

	status = 0;
	ft_stdout = dup(1);
	ft_stdin = dup(0);
	pid = fork();
	if (pid == -1)
	{
		perror("Fork : ");
		return (-1);
	}
	if (pid == 0)
	{
		if (handle_redirect(exec->head, envp, ft_stdin, ft_stdout) == -1)
			finish_process(exec, tokens, envp, input);
		handle_execution(exec->head, envp);
		finish_process(exec, tokens, envp, input);
	}
	else
		wait_for_children(envp, &pid);
	return (0);
}
