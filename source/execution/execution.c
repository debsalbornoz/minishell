/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/16 22:33:42 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*execute(t_list *lst_tokens, t_list *lst_exec, t_list *lst_env)
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(0);
	fd_out = dup(1);
	(void)lst_env;
	lst_exec = create_lst_exec(lst_tokens, lst_exec, lst_env);
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	close_fds();
	if (lst_exec->node)
		lst_exec->node = lst_exec->head;
	return (lst_exec);
}

t_list	*create_lst_exec(t_list *tokens, t_list *exec, t_list *envp)
{
	t_node	*aux;

	aux = tokens->head;
	while (aux)
	{
		if ((aux == tokens->head && (aux->data->token->type == COMMAND
					|| aux->data->token->type == PATH))
			|| (aux->data->token->type == PIPE
				&& (aux->next->data->token->type == COMMAND
					|| aux->next->data->token->type == PATH)))
		{
			exec = add_node(exec);
			exec->node->data = ft_calloc(1, sizeof(union u_data));
			exec->node->data->execution = ft_calloc(1, sizeof(t_exec));
			exec->node->data->execution->envp = env_list_to_str_array(envp);
		}
		aux = aux->next;
	}
	if (exec->node)
	{
		create_command_table(tokens, exec);
		fill_path_in_exec(tokens, exec, envp);
		exec->node = exec->head;
	}
	return (exec);
}
