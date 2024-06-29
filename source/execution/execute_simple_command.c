/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/06/29 15:51:56 by dlamark-         ###   ########.fr       */
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
	char	*sts;

	status = 0;
	ft_stdout = dup(1);
	ft_stdin = dup(0);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		handle_redirect(exec->head, envp, ft_stdin, ft_stdout);
		handle_execution(exec->head, envp);
		ft_stdout = dup2(ft_stdout, 1);
		ft_stdin = dup2(ft_stdin, 0);
		if (exec->node->data->exec->command_table
			&& exec->node->data->exec->path == NULL
			&& ft_strncmp("126", ft_get_env("?"), 3) != 0)
		{
			update_env_list(envp, "?", "127");
			ft_putstr_fd("command not found\n", 2);
		}
		finish_process(exec, tokens, envp, input);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			sts = ft_itoa(WEXITSTATUS(status));
			update_env_list(envp, "?", sts);
			free (sts);
		}
	}
	return (0);
}
