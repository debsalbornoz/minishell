/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:32:29 by codespace         #+#    #+#             */
/*   Updated: 2024/06/28 14:15:35 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void setup_pipes(int command_index, int fd_in, int fd_out, int **pipes, int num_pipes);

void execute_commands(t_list *exec, int num_pipes, int **pipes, int fd_in, int fd_out, t_list *envp)
{
	int		command_index;
	t_node	*node;
	pid_t	pid;

	command_index = 0;
	node = exec->head;
	while (node != NULL)
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			handle_redirect(node, envp);
			setup_pipes(command_index, fd_in, fd_out, pipes, num_pipes);
			handle_execution(node, envp);
		}
		else
		{
			close_pipes(command_index, pipes, num_pipes);
			node = node->next;
			command_index++;
		}
	}
}
void setup_pipes(int command_index, int fd_in, int fd_out, int **pipes, int num_pipes)
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

void restore_file_descriptors(int fd_in, int fd_out)
{
	dup2(fd_in, 0);
	dup2(fd_out, 1);
}

void wait_for_children(int *status, t_list *envp)
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

int execute_multiple_commands(t_list *exec, t_list *tokens, t_list *envp, char *input)
{
	(void)tokens;
	(void)input;

	int status;
	int num_pipes;
	int **pipes;
	int fd_in;
	int fd_out;

	status = 0;
	num_pipes = count_pipes(exec);
	pipes = create_pipes(num_pipes);
	if (!pipes)
		return (-1);
	fd_in = dup(0);
	fd_out = dup(1);
	execute_commands(exec, num_pipes, pipes, fd_in, fd_out, envp);
	restore_file_descriptors(fd_in, fd_out);
	wait_for_children(&status, envp);
	return (0);
}

