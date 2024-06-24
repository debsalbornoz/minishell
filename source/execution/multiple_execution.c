/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:13:07 by codespace         #+#    #+#             */
/*   Updated: 2024/06/21 16:52:12 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*execute_multi_commands(t_list *exec, t_list *tokens, char *input, t_list *envp)
{
	t_node	*aux;
	int		pid;
	int		ft_stdout;
	int		ft_stdin;
	int		status;
	char	*sts;

	status = 0;
	ft_stdout = dup(1);
	ft_stdin = dup(0);
	aux = exec->head;
	while (aux)
	{
		pid = fork();
		if (pid == -1)
			return (NULL);
		if (pid == 0)
		{
			redirect_and_execute(exec->node, envp);
			ft_stdout = dup2(ft_stdout, 1);
			ft_stdin = dup2(ft_stdin, 0);
			if (exec->node->data->exec->command_table
				&& exec->node->data->exec->path == NULL)
			{
				update_env_list(envp, "?", "127");
				ft_putstr_fd("Command not found\n", 2);
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
		aux = aux->next;
	}
	return (exec);
}
