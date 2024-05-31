/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:15:57 by dlamark-          #+#    #+#             */
/*   Updated: 2024/05/31 15:37:30 by jraupp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_multiple_commands(t_list *exec, t_list *tokens,
			t_list *env, char *input);

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
			execute_simple_command(lst_exec, lst_tokens, lst_env, input);
	}
	close_fds();
	if (lst_exec->node)
		lst_exec->node = lst_exec->head;
	return (release_memory(lst_tokens, lst_exec, input), output);
}

void	print_lst_exec(t_list *lst_exec, t_list *envp)
{
	t_list	*aux;

	aux = 0;
	aux->node = lst_exec->head;
	while (aux)
	{
		if (is_command(aux->node->data->token->type)
			|| aux->node->data->token->type == PATH)
		{
			aux = add_node(aux);
			aux->node->data = ft_calloc(1, sizeof(union u_data));
			aux->node->data->exec->envp = env_list_to_str_array(envp);
		}
		aux->node = aux->node->next;
	}
}

int	validate_command(t_node *exec, t_list *envp)
{
	if (exec->data->exec->path != NULL
		&& exec->data->exec->command_table != NULL
		&& exec->data->exec->envp != NULL)
		return (1);
	if (exec->data->exec->command_table == NULL)
	{
		update_env_list(envp, "?", "127");
		printf("Command not found\n");
	}
	return (0);
}
