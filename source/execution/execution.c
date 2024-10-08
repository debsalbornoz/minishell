/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:22:10 by dlamark-          #+#    #+#             */
/*   Updated: 2024/07/28 19:44:34 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute(t_list *lst_tokens, t_list *lst_exec,
	t_list *lst_env, char *input)
{
	int	status;
	int	fd_in;
	int	fd_out;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	status = 0;
	lst_exec = create_lst_exec(lst_tokens, lst_exec, lst_env);
	if (!lst_exec)
		return (0);
	if (is_simple_command(lst_tokens))
	{
		if (is_builtin2(lst_tokens))
		{
			status = builtins(lst_exec, lst_env, fd_in, fd_out);
			restore_file_descriptors(fd_in, fd_out);
		}
		else
			execute_simple_command(lst_exec, lst_tokens, lst_env, input);
	}
	else
		execute_multiple_commands(lst_exec, lst_tokens, lst_env, input);
	if (lst_exec->node)
		lst_exec->node = lst_exec->head;
	return (release_memory(lst_tokens, lst_exec, input), status);
}

int	handle_execution(t_node *exec, t_list *envp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execute_builtins(exec, envp))
		return (-1);
	if (!execute_builtins(exec, envp))
	{
		if (validate_command(exec))
		{
			if (execve(exec->data->exec->path,
					exec->data->exec->command_table,
					exec->data->exec->envp) == -1)
				return (-1);
		}
		if (exec->data->exec->command_table
			&& exec->data->exec->path == NULL
			&& ft_strncmp("126", ft_get_env("?"), 3) != 0)
		{
			update_env_list(envp, "?", "127");
			ft_putstr_fd(" command not found\n", 2);
			return (-1);
		}
	}
	return (0);
}

void	restore_file_descriptors(int fd_in, int fd_out)
{
	dup2(fd_in, 0);
	dup2(fd_out, 1);
}
