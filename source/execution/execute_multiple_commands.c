/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:32:29 by codespace         #+#    #+#             */
/*   Updated: 2024/07/09 19:06:49 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_multiple_commands(t_list *exec, t_list *tokens,
			t_list *envp, char *input)
{
	int			num_pipes;
	int			**pipes;
	int			fd_in;
	int			fd_out;
	static int	*pids;

	num_pipes = count_pipes(exec);
	pipes = create_pipes(num_pipes);
	pids = ft_calloc((count_nodes(exec) + 1), sizeof(int));
	if (!pipes)
		return (-1);
	fd_in = dup(0);
	fd_out = dup(1);
	if (handle_multi_exec(exec, num_pipes, pipes, pids) == -1)
		finish_process(exec, tokens, envp, input);
	restore_file_descriptors(fd_in, fd_out);
	wait_for_children(envp, pids);
	free_pipes(pipes);
	free(pids);
	return (0);
}

int	handle_multi_exec(t_list *exec, int num_pipes, int **pipes, int *pids)
{
	t_node	*node;
	int		i;
	int		*std_fds;

	(void)num_pipes;
	std_fds = ft_calloc(2, sizeof(int));
	std_fds[0] = dup(0);
	std_fds[1] = dup(1);
	i = 0;
	node = exec->head;
	while (node != NULL)
	{
		if (fork_and_execute_command(std_fds, pipes,
				node, pids[i]) == -1)
			return (-1);
		node = node->next;
		i++;
	}
	free(std_fds);
	return (0);
}

int	fork_and_execute_command(int *std_fds,
		int **pipes, t_node *node, int pid)
{
	int		i;
	t_list	*envp;

	i = 0;
	pid = fork();
	envp = data_env_addr();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		setup_pipes(node->data->exec->index, std_fds[0], std_fds[1], pipes);
		if (handle_redirect(node, envp, std_fds[0], std_fds[1]) == -1)
			return (-1);
		if (handle_execution(node, envp) == -1)
			return (-1);
		restore_file_descriptors(std_fds[0], std_fds[1]);
	}
	else
	{
		restore_file_descriptors(std_fds[0], std_fds[1]);
		close_pipes(node->data->exec->index, pipes, count_pipes2(pipes));
	}
	return (0);
}
