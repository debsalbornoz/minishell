/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:32:29 by codespace         #+#    #+#             */
/*   Updated: 2024/07/01 13:46:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_commands(t_list *exec, int num_pipes, int **pipes, t_list *envp)
{
	int		command_index;
	t_node	*node;
	pid_t	pid;
	int		ft_stdin;
	int		ft_stdout;

	ft_stdin = dup(0);
	ft_stdout = dup(1);
	command_index = 0;
	node = exec->head;
	while (node != NULL)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			setup_pipes(command_index, ft_stdin, ft_stdout, pipes);
			if (handle_redirect(node, envp, ft_stdin, ft_stdout) == -1)
				return (-1);
			handle_execution(node, envp);
			restore_file_descriptors(ft_stdin, ft_stdout);
			exit(EXIT_SUCCESS);
		}
		else
		{
			restore_file_descriptors(ft_stdin, ft_stdout);
			close_pipes(command_index, pipes, num_pipes);
			node = node->next;
			command_index++;
		}
	}
	return (0);
}

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
	if (execute_commands(exec, num_pipes, pipes, envp) == -1)
		finish_process(exec, tokens, envp, input);
	restore_file_descriptors(fd_in, fd_out);
	wait_for_children(&status, envp);
	return (0);
}
