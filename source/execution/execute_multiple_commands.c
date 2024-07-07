/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:32:29 by codespace         #+#    #+#             */
/*   Updated: 2024/07/07 16:27:24 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_multiple_commands(t_list *exec, t_list *tokens,
			t_list *envp, char *input)
{
	int	status;
	int	num_pipes;
	int	**pipes;
	int	fd_in;
	int	fd_out;

	status = 0;
	num_pipes = count_pipes(exec);
	pipes = create_pipes(num_pipes);
	if (!pipes)
		return (-1);
	fd_in = dup(0);
	fd_out = dup(1);
	if (handle_multi_exec(exec, num_pipes, pipes) == -1)
		finish_process(exec, tokens, envp, input);
	restore_file_descriptors(fd_in, fd_out);
	wait_for_children(&status, envp);
	free_pipes(pipes);
	return (0);
}

int	handle_multi_exec(t_list *exec, int num_pipes, int **pipes)
{
	t_node	*node;
	int		ft_stdin;
	int		ft_stdout;

	(void)num_pipes;
	ft_stdin = dup(0);
	ft_stdout = dup(1);
	node = exec->head;
	while (node != NULL)
	{
		if (fork_and_execute_command(ft_stdin, ft_stdout, pipes, node) == -1)
			return (-1);
		node = node->next;
	}
	return (0);
}

int	fork_and_execute_command(int ft_stdin, int ft_stdout,
		int **pipes, t_node *node)
{
	pid_t	pid;
	t_list	*envp;

	pid = fork();
	envp = data_env_addr();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		setup_pipes(node->data->exec->index, ft_stdin, ft_stdout, pipes);
		if (handle_redirect(node, envp, ft_stdin, ft_stdout) == -1)
			return (-1);
		if (handle_execution(node, envp) == -1)
		{
			printf("?\n");
			return (-1);
		}
		restore_file_descriptors(ft_stdin, ft_stdout);
	}
	else
	{
		restore_file_descriptors(ft_stdin, ft_stdout);
		close_pipes(node->data->exec->index, pipes, count_pipes2(pipes));
	}
	return (0);
}
