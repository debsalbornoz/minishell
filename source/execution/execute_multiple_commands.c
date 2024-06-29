/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:32:29 by codespace         #+#    #+#             */
/*   Updated: 2024/06/29 16:17:14 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	setup_pipes(int command_index, int fd_in, int fd_out,
			int **pipes, int num_pipes);
void	restore_file_descriptors(int fd_in, int fd_out);

void	execute_commands(t_list *exec, int num_pipes, int **pipes,
		int fd_in, int fd_out, t_list *envp, char *input, t_list *tokens)
{
	int		command_index;
	t_node	*node;
	pid_t	pid;
	int		ft_stdin;
	int		ft_stdout;

	(void) fd_out;
	(void) fd_in;
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
			setup_pipes(command_index, ft_stdin, ft_stdout, pipes, num_pipes);
			if (handle_redirect(node, envp, ft_stdin, ft_stdout) == -1)
				finish_process(exec, tokens,envp, input);
			handle_execution(node, envp);
			restore_file_descriptors(ft_stdin, ft_stdout);
			exit(EXIT_SUCCESS);
		}
		else
		{
			restore_file_descriptors(fd_in, fd_out);
			close_pipes(command_index, pipes, num_pipes);
			node = node->next;
			command_index++;
		}
	}
}

void	restore_file_descriptors(int fd_in, int fd_out)
{
	dup2(fd_in, 0);
	dup2(fd_out, 1);
}

void	wait_for_children(int *status, t_list *envp)
{
	char	*sts;

	sts = NULL;
	while (wait(status) > 0);
	if (WIFEXITED(*status))
	{
		sts = ft_itoa(WEXITSTATUS(*status));
		update_env_list(envp, "?", sts);
		free(sts);
	}
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
	execute_commands(exec, num_pipes, pipes, fd_in, fd_out, envp, input, tokens);
	restore_file_descriptors(fd_in, fd_out);
	wait_for_children(&status, envp);
	return (0);
}

void setup_pipes(int command_index, int fd_in,
			int fd_out, int **pipes, int num_pipes)
{
	int		i;

	i = 0;
	if (command_index > 0)
		dup2(pipes[command_index - 1][0], 0);
	else
		dup2(fd_in, 0);
	if (command_index < num_pipes)
		dup2(pipes[command_index][1], 1);
	else
		dup2(fd_out, 1);
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
