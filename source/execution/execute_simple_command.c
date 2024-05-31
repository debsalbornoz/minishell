/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/30 21:22:31 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_simple_command(t_list *tokens)
{
	t_node	*aux;

	aux = tokens->head;
	while (aux != NULL)
	{
		if (aux->data->token->type == PIPE)
			return (0);
		aux = aux->next;
	}
	aux = tokens->head;
	return (1);
}

int	execute_simple_command(t_list *exec,
	t_list *tokens, t_list *envp, char *input)
{
	redirect_and_execute(exec->node, tokens, envp, input);
	return (0);
}
void	redirect_and_execute(t_node *exec, t_list *tokens,
	t_list *envp, char *input)
{
	int	pid;
	int	ft_stdout;
	int	ft_stdin;
	handle_heredoc(exec);
	ft_stdout = dup(1);
	ft_stdin = dup(0);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		handle_redirect(exec);
		if (validate_command(exec, envp))
		{
			if (execve(exec->data->execution->path,
				exec->data->execution->command_table,
				exec->data->execution->envp) == -1)
				{
					ft_stdout = dup2(ft_stdout, 1);
					ft_stdin = dup2(ft_stdin, 0);
					finish_process(exec, tokens, envp, input);
				}
		}
	}
	else
		waitpid(pid, NULL, 0);
}


void	finish_process(t_node *exec, t_list *tokens, t_list *envp, char *input)
{
	t_list	*lst_exec;
	(void)exec;

	lst_exec = init_exec_addr();
	free_list(lst_exec, free_lst_exec);
	free_list(tokens, free_lst_tokens);
	free_list(envp, free_lst_env);
	free(input);
	close_fds();
	exit(2);
}

