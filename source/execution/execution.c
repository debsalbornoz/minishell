/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/07 20:27:28 by codespace        ###   ########.fr       */
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
	lst_exec = create_lst_exec(lst_tokens,lst_exec, lst_env);
	//lst_tokens = handle_redirect(lst_tokens);
	//lst_exec = prepare_for_execution(lst_tokens, lst_exec, lst_env);
	//if (lst_exec->node->data->execution ->path != NULL)
	//	execute_simple_command(lst_exec);
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	close_fds();
	lst_exec->node = lst_exec->head;
	return (lst_exec);
}

t_list	*create_lst_exec(t_list *tokens, t_list *exec, t_list *envp)
{
	t_node	*aux;
	int		i;

	i = 0;
	aux = tokens->head;
	while (aux)
	{
		if (aux == tokens->head || aux->data->token->type == PIPE)
		{
			exec = add_node(exec);
			exec->node->data = ft_calloc(1, sizeof(union u_data));
			exec->node->data->execution = ft_calloc(1, sizeof(t_exec));
			exec->node->data->execution->envp = env_list_to_str_array(envp);
			i++;
		}
		aux = aux->next;
	}
	create_command_table(tokens, exec);
	return (exec);
}

/*t_list	*prepare_for_execution(t_list *tokens, t_list *exec, t_list *envp)
{

	exec->node->data->execution
		->path = find_executable_in_path(exec, tokens, envp);
	exec->node = exec->head;
	tokens->node = tokens->head;
	return (exec);
}
*/
