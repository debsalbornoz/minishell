/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jackson <jackson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/29 05:26:17 by jackson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_command_table(char **command_table);

int	execute(t_list *lst_tokens, t_list *lst_exec, t_list *lst_env, char *input)
{
	int	output;

	output = 0;
	lst_exec = create_lst_exec(lst_tokens, lst_exec, lst_env);
	if (!lst_exec)
		return (output);
	lst_exec->node = lst_exec->head;
	if (is_simple_command(lst_tokens))
	{
		if (is_builtins(lst_tokens->node->data->token->type))
			output = builtins(lst_tokens, lst_exec, lst_env);
		else
			execute_simple_command(lst_exec, lst_tokens);
	}
	if (lst_exec->node)
		lst_exec->node = lst_exec->head;
	return (release_memory(lst_tokens, lst_exec, input), output);
}

t_list	*create_lst_exec(t_list *tokens, t_list *exec, t_list *envp)
{
	t_node	*aux;

	aux = tokens->head;
	while (aux)
	{
		if (is_command(aux->data->token->type)
			|| aux->data->token->type == PATH)
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
		//get_redirects_and_files(exec, tokens);
		exec->node = exec->head;
	}
	return (exec);
}
