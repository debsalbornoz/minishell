/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/29 14:56:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_multiple_commands(t_list *exec, t_list *tokens,
			t_list *env, char *input);

t_list	*execute(t_list *lst_tokens, t_list *lst_exec,
	t_list *lst_env, char *input)
{
	lst_exec = create_lst_exec(lst_tokens, lst_exec, lst_env);
	if (!lst_exec)
		return (NULL);
	if (is_simple_command(lst_tokens))
		execute_simple_command(lst_exec, lst_tokens, lst_env, input);
	else
		execute_multiple_commands(lst_exec, lst_tokens, lst_env, input);
	close_fds();
	if (lst_exec->node)
		lst_exec->node = lst_exec->head;
	return (lst_exec);
}

void	execute_multiple_commands(t_list *exec, t_list *tokens,
			t_list *env, char *input)
{
	int		fd[2];
	int		pid;

	exec->node = exec->head;
	if (pipe(fd) == -1)
		return ;
	while (exec->node)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			handle_redirect(exec->node);
			dup2(fd[1], STDOUT_FILENO);
			pid = fork();
			if (pid == 0)
			{
				if (validate_command(exec->node, env))
				{
					pid = fork();
					if (pid == 0)
					{
						if (execve(exec->node->data->execution->path,
								exec->node->data->execution->command_table,
								exec->node->data->execution->envp) == -1)
							finish_process(exec->node, tokens, env, input);
						else
						{
							waitpid(pid, NULL, 0);
							finish_process(exec->node, tokens, env, input);
						}
					}
				}
				else
				{
					waitpid(pid, NULL, 0);
					finish_process(exec->node, tokens, env, input);
				}
			}
			else
				waitpid(pid, NULL, 0);
		}
		exec->node = exec->node->next;
	}
}

void	print_lst_exec(t_list *lst_exec)
{
	t_node	*aux;

	aux = lst_exec->head;
	while (aux)
	{
		printf("command_table : ");
		print_matrix(aux->data->execution->command_table);
		printf("\n redirects and files:");
		print_matrix(aux->data->execution->redirects_and_files);
		printf("\npath : %s\n", aux->data->execution->path);
		aux = aux->next;
	}
}

int	validate_command(t_node *exec, t_list *envp)
{
	if (exec->data->execution->path != NULL
		&& exec->data->execution->command_table != NULL
		&& exec->data->execution->envp != NULL)
		return (1);
	if (exec->data->execution->command_table == NULL)
	{
		update_env_list(envp, "?", "127");
		printf("Command not found\n");
	}
	return (0);
}
